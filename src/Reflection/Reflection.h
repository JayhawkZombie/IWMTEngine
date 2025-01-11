//
// Created by Kurt Slagle on 1/4/25.
//

#pragma once

#include <entt/entt.hpp>
using namespace entt::literals;

namespace Reflection {
    inline auto GetHashedString(const std::string& str) {
        return entt::hashed_string(str.c_str());
    }

    inline auto GetHashedString(const char *str) {
        return entt::hashed_string(str);
    }

    inline auto GetMeta(const std::string &str) {
        const auto hashed = GetHashedString(str);
        return entt::resolve(hashed);
    }

    inline auto GetMeta(const char *str) {
        const auto hashed = GetHashedString(str);
        return entt::resolve(hashed);
    }
}
