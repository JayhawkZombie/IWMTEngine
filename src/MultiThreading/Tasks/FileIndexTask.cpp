//
// Created by Kurt Slagle on 12/31/24.
//

#include "FileIndexTask.h"

FileIndexTask::FileIndexTask(const std::filesystem::path &rootPath): root(rootPath) {
}

std::vector<std::filesystem::path> FileIndexTask::operator()() const {
    std::vector<std::filesystem::path> result;
    for (const auto &entry : std::filesystem::directory_iterator(root)) {
        if (entry.is_regular_file()) {
            result.push_back(entry.path());
        }
    }
    return result;
}
