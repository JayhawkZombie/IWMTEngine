//
// Created by Kurt Slagle on 12/30/24.
//

#include "WorkerThread.h"
#include <entt/entt.hpp>

const WorkerThread::TaskT WorkerThread::NoOp = []() {return std::make_shared<entt::meta_any>();};

// auto fmt::formatter<WorkerThread>::format(const WorkerThread &worker, fmt::format_context &ctx) const {
//     return fmt::formatter<fmt::string_view>::format(worker.name, ctx);
// }
