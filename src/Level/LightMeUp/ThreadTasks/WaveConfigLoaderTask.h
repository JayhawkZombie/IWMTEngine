//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <entt/meta/meta.hpp>

class WaveCofigLoaderTask {
public:
    std::filesystem::path root;
    explicit WaveCofigLoaderTask(const std::filesystem::path &rootPath);

    std::shared_ptr<entt::meta_any> operator()() const;
};
