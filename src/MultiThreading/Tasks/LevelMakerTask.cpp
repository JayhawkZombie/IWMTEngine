//
// Created by Kurt Slagle on 1/4/25.
//

#include "LevelMakerTask.h"
#include <Logging/LogFormatting.h>
#include <Reflection/Reflection.h>

#include <utility>

LevelMakerTask::LevelMakerTask(std::string className) : levelClassName{std::move(className)} {

}

std::shared_ptr<entt::meta_any> LevelMakerTask::operator()() const {
    // std::shared_ptr<Level> maybeLevel;
    // if (!levelClassName.empty()) {
    //     const auto meta = Reflection::GetMeta(levelClassName);
    //     if (!meta) {
    //         fmt::println("Failed to load level {}",
    //                      fmt::styled(levelClassName, fg_color_red));
    //     } else {
    //         fmt::println("Resolved level class metadata: {}",
    //                      fmt::styled(meta.info().name(), fg_color_green));
    //         auto maybeLevelPtr = meta.construct();
    //
    //         if (!maybeLevelPtr) {
    //             fmt::println("Failed to construct level class {}",
    //                          fmt::styled(meta.info().name(), fg_color_red));
    //         }
    //         if (auto ptr = maybeLevelPtr.try_cast<Level>(); ptr) {
    //             fmt::println("Level {}", fmt::styled(levelClassName, fg_color_green));
    //             // I think it's going boom here, going out of scope and level is being destroyed
    //             maybeLevel = std::shared_ptr<Level>(ptr);
    //         }
    //     }
    // } else {
    //     fmt::println("No level class provided to task");
    // }
    // return std::move(maybeLevel);
    std::shared_ptr<entt::meta_any> maybeAny(nullptr);
    if (!levelClassName.empty()) {
        const auto meta = Reflection::GetMeta(levelClassName);
        if (!meta) {
            fmt::println("Failed to load level {}",
                         fmt::styled(levelClassName, fg_color_red));
        } else {
            fmt::println("Resolved level class metadata: {}",
                         fmt::styled(meta.info().name(), fg_color_green));
            auto maybeLevelPtr = std::make_shared<entt::meta_any>(meta.construct());

            if (!maybeLevelPtr) {
                fmt::println("Failed to construct level class {}",
                             fmt::styled(meta.info().name(), fg_color_red));
                return maybeAny;
            }
            return maybeLevelPtr;
        }
    } else {
        fmt::println("No level class provided to task");
    }
    return maybeAny;
}
