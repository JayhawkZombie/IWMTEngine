//
// Created by Kurt Slagle on 1/12/25.
//

#pragma once

#include <Engine/GameObject.h>
#include <Level/TestBed/SpriteSheet.h>

class Block : public GameObject {
public:
    sf::Sprite sprite;
    SpriteSheet *spriteSheet;


    void Tick(double delta) override;
    void Init() override;
    void Render(sf::RenderTarget &target) override;
};
