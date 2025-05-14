//
// Created by Kurt Slagle on 5/14/25.
//

#pragma once

#include <Globals.h>
#include <algorithm>
#include <filesystem>
#include <fmt/base.h>

class AssetProcessor {
public:
    static std::array<std::string, 10> KnownAssetExtensions;

    static bool IsKnownAssetExtension(const std::filesystem::path &extension) {
        return std::find(KnownAssetExtensions.begin(),
                         KnownAssetExtensions.end(),
                         extension) != KnownAssetExtensions.end();
    }

    static bool IsInHiddenFolder(const std::filesystem::path &path) {
        const auto rootPath             = path.parent_path();
        const auto startsWithDot        = rootPath.string().starts_with('.');
        const auto startsWithUnderscore = rootPath.string().starts_with('_');
        return startsWithUnderscore || startsWithDot;
    }

    static bool IsPossiblyAsset(const std::filesystem::path &path) {
        const auto relPath = std::filesystem::relative(path, "./");
        const auto isFile   = std::filesystem::is_regular_file(relPath);
        if (!isFile) {
            return false;
        }
        const auto rootPath = relPath.relative_path();
        if (IsInHiddenFolder(rootPath)) {
            return false;
        }
        if (IsKnownAssetExtension(rootPath.extension())) {
            return true;
        }
        return false;
    }
};
