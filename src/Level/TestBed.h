//
// Created by Kurt Slagle on 1/4/25.
//

#pragma once

#include "Level.h"
#include "TestBed/SpriteSheet.h"

class TestBed : public Level {
public:
    TestBed()           = default;
    ~TestBed() override = default;

    void Init() override;
    void Tick(double delta) override;
    void Render(sf::RenderTarget &target) override;
    bool RenderEditor() override;
    SpriteSheet sprite_sheet;
};

inline bool TestBed::RenderEditor() {
    return Level::RenderEditor();
}

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(TestBed)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_END(TestBed)
