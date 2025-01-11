//
// Created by Kurt Slagle on 1/1/25.
//

#pragma once

#include <Physics/Physics.h>

#include <cereal/cereal.hpp>

template<class Archive>
void serialize(Archive &ar, vec2d &vec) {
    ar(vec.x, vec.y);
}
