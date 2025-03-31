//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

// Empty macro, searched for by the codegen
#define RENGINE_REFLECT_CLASS_BEGIN(...)
#define RENGINE_REFLECT_CLASS_MEMBER(...)
#define RENGINE_REFLECT_BASE_CLASS(...)
#define RENGINE_REFLECT_CLASS_END(...)

#include <cereal/access.hpp>

// NOT empty macro, adds friend class needed for non-public serialization
#define RENGINE_PRIVATE_SERIALIZATION \
    friend class cereal::access;

extern void Reflect_RegisterAll();
