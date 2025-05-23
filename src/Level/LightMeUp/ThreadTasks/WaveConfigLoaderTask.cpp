//
// Created by Kurt Slagle on 12/31/24.
//

#include "WaveConfigLoaderTask.h"

#include <fmt/base.h>

WaveCofigLoaderTask::WaveCofigLoaderTask(const std::filesystem::path &rootPath): root(rootPath) {
}

std::shared_ptr<entt::meta_any> WaveCofigLoaderTask::operator()() const {
    auto files = std::vector<std::filesystem::path>();
    for (const auto &entry : std::filesystem::recursive_directory_iterator(root)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    std::shared_ptr<entt::meta_any> result = std::make_shared<
        entt::meta_any>(files);
    return result;
}
