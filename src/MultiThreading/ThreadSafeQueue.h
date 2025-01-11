//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

#include <queue>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;

public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    void Push(const T &data) {
        std::lock_guard lock(mutex);
        queue.push(data);
        condition.notify_one();
    }
    bool TryGetTop(T &data) {
        std::lock_guard lock(mutex);
        if (queue.empty()) {
            return false;
        }
        data = queue.front();
        return true;
    }
    bool TryPop(T &item) {
        std::lock_guard lock(mutex);
        if (queue.empty()) {
            return false;
        }
        item = std::move(queue.front());
        queue.pop();
        return true;
    }
    void WaitAndPop(T &data) {
        std::lock_guard lock(mutex);
        condition.wait(lock, [&]() { return !queue.empty(); });
        data = std::move(queue.front());
        queue.pop();
    }
    bool Empty() {
        std::lock_guard lock(mutex);
        return queue.empty();
    }
};
