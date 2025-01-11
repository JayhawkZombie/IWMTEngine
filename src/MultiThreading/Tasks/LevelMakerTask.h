//
// Created by Kurt Slagle on 1/4/25.
//

#pragma once
#include <string>
#include <entt/entt.hpp>
#include <Level/Level.h>

class LevelMakerTask {
public:
    std::string levelClassName;
    explicit LevelMakerTask(std::string className);
    std::shared_ptr<entt::meta_any> operator()() const;
};
