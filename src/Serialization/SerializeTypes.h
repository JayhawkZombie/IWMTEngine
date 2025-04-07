//
// Created by Kurt Slagle on 1/1/25.
//

#pragma once

#include <Physics/Physics.h>
#include <SFML/Graphics.hpp>

#include <cereal/cereal.hpp>

template<class Archive>
void serialize(Archive &ar, vec2d &vec) {
    ar(vec.x, vec.y);
}

namespace cereal {
    template<class Archive>
    void serialize(Archive &ar, sf::Vector2f &vec) {
        ar(cereal::make_nvp("x", vec.x),
           cereal::make_nvp("y", vec.y));
    }

    template<class Archive>
    void serialize(Archive &ar, sf::Vector2i &vec) {
        ar(cereal::make_nvp("x", vec.x),
           cereal::make_nvp("y", vec.y));
    }

    template<class Archive>
    void serialize(Archive &ar, sf::Vector2u &vec) {
        ar(cereal::make_nvp("x", vec.x),
           cereal::make_nvp("y", vec.y));
    }
}
