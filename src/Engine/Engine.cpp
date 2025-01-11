//
// Created by Kurt Slagle on 12/31/24.
//

#include "Engine.h"
#include <iostream>
#include <thread>
#include <fmt/format.h>
#include <MultiThreading/WorkerThread.h>
#include <MultiThreading/Tasks/FileIndexTask.h>
#include <SFML/Window.hpp>

void Engine::CheckIndexedFiles(const std::vector<std::filesystem::path> &paths) {
    fmt::println("Checking indexed files ({})...", paths.size());
    for (const auto &path : paths) {
        fmt::print("\t{}\n", path.string());
    }
}


void Engine::CheckWorkerResults() {
    WorkerThread::ResultQueueItemT item;
    if (engineWorker.TryPopResult(item)) {
        fmt::println("Engine popping worker thread result: {}", item.second);
        if (auto cast_paths = item.first->try_cast<std::vector<std::filesystem::path>>(); cast_paths) {
            CheckIndexedFiles(*cast_paths);
        } else if (auto level = item.first->try_cast<std::shared_ptr<Level>>(); level) {
            fmt::println("Got level from worker");
            maybeCurrentLevel = *level;
        }
    }
}


int Engine::Run() {
    // WorkerThread worker;
    engineWorker.Start();
    // engineWorker.PostTask(FileIndexTask(std::filesystem::current_path()), "FileIndexTask");

    GameLoop();

    window->close();
    return 0;
}

void Engine::RequestQuit() {
    std::cerr << "Request quit" << std::endl;
    quit = true;
}
