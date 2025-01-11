//
// Created by Kurt Slagle on 1/4/25.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class SpriteSheet {
public:

    std::string originalFileName{};
    std::shared_ptr<sf::Texture> texture = nullptr;
    sf::IntRect dimensions = {0, 0, 0, 0};
    std::vector<sf::IntRect> rawFrames{};
    std::unordered_map<std::string, sf::IntRect> namedFrames{};

    SpriteSheet() = default;
    ~SpriteSheet() = default;

    explicit SpriteSheet(const std::string& fileName);
    bool Load(const std::string& fileName);
    void Render(sf::RenderTarget& target, const sf::Vector2f &position);

    void RenderEditor();
    void RenderMenuBar();
    void RenderFrameEditorPopup();
    void RenderFrameEditorForFrame(int frame);
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(SpriteSheet)
RENGINE_REFLECT_CLASS_MEMBER(sf::IntRect, dimensions, "dimensions")
RENGINE_REFLECT_CLASS_MEMBER(std::vector<sf::IntRect>, rawFrames, "rawFrames")
RENGINE_REFLECT_CLASS_MEMBER(std::unordered_map<std::string, sf::IntRect>, namedFrames, "namedFrames")
RENGINE_REFLECT_CLASS_END(SpriteSheet)
