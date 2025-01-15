//
// Created by Kurt Slagle on 1/12/25.
//

#pragma once

#include <Level/Level.h>
#include "../TestBed/SpriteSheet.h"
#include "Block.h"

class TarmieLevel : public Level {
public:
    SpriteSheet m_spriteSheet;
    int m_worldBlockSizePx = 25;
    // std::vector<Block> m_blocks;
    std::vector<sf::Vertex> m_gridLineVertices;

    TarmieLevel();
    ~TarmieLevel() override;

    void Init() override;
    void Render(sf::RenderTarget &target) override;
    void RenderGrid(sf::RenderTarget &target);
    void RenderEditor() override;
    void Tick(double delta) override;

    void AdjustToNewBlockSize();
    void CreateGridLines();
    sf::Vector2i GetGridCoord(const sf::Vector2i &pos);
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(TarmieLevel)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_MEMBER(SpriteSheet, m_spriteSheet, "spriteSheet")
RENGINE_REFLECT_CLASS_END(TarmieLevel)
