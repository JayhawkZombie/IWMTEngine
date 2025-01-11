//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <functional>
#include <MultiThreading/ThreadSafeQueue.h>
#include <entt/entt.hpp>
#include <fmt/color.h>
#include <fmt/format.h>

class WorkerThread {
public:
    using TaskT = std::function<std::shared_ptr<entt::meta_any>()>;

    static const TaskT NoOp;

    struct TaskNodeT {
        TaskT task       = NoOp;
        std::string name = "unnamed-task";

        TaskNodeT() = default;

        TaskNodeT(const TaskT &t, const std::string &n) : task(t), name(n) {
        }

        TaskNodeT(const TaskNodeT &other) : task(other.task), name(other.name) {
        }

        TaskNodeT(TaskNodeT &&other) noexcept : task(std::move(other.task)),
                                                name(std::move(other.name)) {
        }

        TaskNodeT &operator=(const TaskNodeT &other) {
            task = other.task;
            name = other.name;
            return *this;
        }

        TaskNodeT &operator=(TaskNodeT &&other) noexcept {
            task = std::move(other.task);
            name = std::move(other.name);
            return *this;
        }

        auto operator()() {
            return task();
        }
    };

    using TaskQueueT       = ThreadSafeQueue<TaskNodeT>;
    using ResultQueueItemT = std::pair<std::shared_ptr<entt::meta_any>, std::string>;
    using ResultQueueT     = ThreadSafeQueue<ResultQueueItemT>;

public:
    std::string name = "worker";

    struct Heartbeat {
        std::chrono::steady_clock::time_point time;
        bool goingToSleep = false;

        Heartbeat() : time(std::chrono::steady_clock::now()) {}
    };

private:
    std::thread th;
    std::unique_ptr<TaskQueueT> taskQueue;
    std::atomic_bool running          = false;
    std::atomic_bool stopRequested    = false;
    std::atomic_bool heartbeatEnabled = true;
    std::mutex mutex;

    // Uh oh, I don't think this queue is thread safe D:
    std::queue<ResultQueueItemT> resultQueue;

    ThreadSafeQueue<Heartbeat> heartbeatQueue;

    void PostHeartbeat(bool sleeping = false) {
        std::lock_guard lock(mutex);
        static auto lastHeartbeatTime = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();

        const auto heartbeatInterval = std::chrono::milliseconds(1000);
        if (now - lastHeartbeatTime > heartbeatInterval) {
            Heartbeat hb;
            hb.time         = now;
            hb.goingToSleep = sleeping;
            heartbeatQueue.Push(hb);
            lastHeartbeat = hb;
            lastHeartbeatTime = now;
        }
    }

    void Run() {
        lastHeartbeat = Heartbeat{};
        PostHeartbeat(false);
        while (running) {
            TaskNodeT taskNode;

            if (stopRequested) {
                break;
            }

            if (taskQueue->TryPop(taskNode)) {
                fmt::println("WorkerThread starting: {}", taskNode.name);
                const auto nodeName = taskNode.name;
                const auto res      = taskNode();
                fmt::println("WorkerThread finished: {}", taskNode.name);
                PostResult({res, nodeName});
            } else {
                PostHeartbeat(true);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

public:
    Heartbeat lastHeartbeat;

    WorkerThread(const std::string &nameStr = "WorkerThread") : name(nameStr) {
        taskQueue = std::make_unique<TaskQueueT>();
    }

    virtual ~WorkerThread() {
        fmt::println("WorkerThread destroyed: {}", name);
        if (running) {
            fmt::println("WorkerThread still running: {}, stopping...", name);
            Stop();
        }
    }

    Heartbeat GetLastHeartbeat() {
        return lastHeartbeat;
    }

    void Start() {
        running = true;
        th      = std::thread(&WorkerThread::Run, this);
    }

    void Stop() {
        fmt::println("WorkerThread stopping: {}", name);
        stopRequested = true;
        running       = false;
        PostTask(NoOp, "no-op");
        if (th.joinable()) {
            fmt::println("WorkerThread joining: {}", name);
            th.join();
        }
    }

    void PostTask(const TaskT &task, const std::string &name) const {
        fmt::println("WorkerThread posting task: {} -> {}", this->name, name);
        taskQueue->Push({task, name});
    }

    void PostResult(const ResultQueueItemT &result) {
        fmt::println("WorkerThread posting result: {} -> {}",
                     fmt::styled(this->name, fmt::fg(fmt::color::alice_blue)),
                     result.second);
        resultQueue.push(result);
    }

    bool TryGetLastHeartbeat(Heartbeat &hb) {
        return heartbeatQueue.TryPop(hb);
    }

    bool TryPopResult(ResultQueueItemT &result) {
        if (resultQueue.empty()) {
            return false;
        }
        result = std::move(resultQueue.front());
        resultQueue.pop();
        return true;
    }
};

// static auto format_as(const WorkerThread &worker) {
//     return fmt::format("{}", worker.name);
// }
//
// static auto format_as(WorkerThread &worker) {
//     return fmt::format("{}", worker.name);
// }

// template<> struct fmt::formatter<WorkerThread>: fmt::formatter<fmt::string_view> {
//     auto format(const WorkerThread &t, fmt::format_context &ctx) const -> fmt::format_context::iterator;
// };
