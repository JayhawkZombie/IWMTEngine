//
// Created by Kurt Slagle on 12/31/24.
//

#include "Engine.h"

#include <Globals.h>
#include <iostream>
#include <thread>
#include <fmt/format.h>
#include <MultiThreading/WorkerThread.h>
#include <MultiThreading/Tasks/FileIndexTask.h>
#include <SFML/Window.hpp>

void Engine::CheckIndexedFiles(
    const std::vector<std::filesystem::path> &paths) {
    fmt::println("Checking indexed files ({})...", paths.size());
    for (const auto &path: paths) {
        fmt::print("\t{}\n", path.string());
    }
}

bool HasBaseLevelClass(const entt::meta_type &tInfo) {
    using namespace entt::literals;
    for (const auto &tBase: tInfo.base()) {
        if (tBase.second.info().hash() == "Level"_hs) {
            fmt::println("Has base level class {}\n",
                         tBase.second.info().name());
            return true;
        }
    }
    return false;
}


void Engine::CheckWorkerResults() {
    WorkerThread::ResultQueueItemT item;
    if (engineWorker.TryPopResult(item)) {
        fmt::println("Engine popping worker thread result: {}", item.second);
        if (item.first) {
            fmt::println("Type info {}", item.first->type().info().name());
            fmt::println("Use count {}", item.first.use_count());
        } else {
            fmt::println("Nothing returned by worker");
        }

        using namespace entt::literals;
        const auto itemTypeInfo = item.first->type().info();
        const auto tResolved    = entt::resolve(itemTypeInfo);
        if (HasBaseLevelClass(tResolved)) {
            const auto metaAnyTestBed = item.first;
            maybeLevelPtr             = metaAnyTestBed;
        } else {
            if (auto cast_paths = item.first->try_cast<std::vector<
                std::filesystem::path> >(); cast_paths) {
                CheckIndexedFiles(*cast_paths);
            }
        }

        // if (itemTypeInfo.hash() == "TestBed"_hs) {
        //     fmt::println("TestBed Level !{}", itemTypeInfo.name());
        //     const auto metaAnyTestBed = item.first;
        //     maybeLevelPtr = metaAnyTestBed;
        // } else {
        //     if (auto cast_paths = item.first->try_cast<std::vector<std::filesystem::path>>(); cast_paths) {
        //         CheckIndexedFiles(*cast_paths);
        //     }
        // }
    }
}


int Engine::Run() {
    engineWorker.Start();
    GameLoop();
    window->close();
    return 0;
}

void Engine::RequestQuit() {
    std::cerr << "Request quit" << std::endl;
    quit = true;
}
