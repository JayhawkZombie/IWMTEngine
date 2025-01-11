//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <string>
#include <vector>
#include <filesystem>

class FileIndexTask {
public:
    std::filesystem::path root;
    explicit FileIndexTask(const std::filesystem::path &rootPath);

    std::vector<std::filesystem::path> operator()() const;
};
