//
// Created by Kurt Slagle on 1/4/25.
//

#include "TestBed.h"
#include <Logging/LogFormatting.h>

void TestBed::Init() {
    fmt::println("{}",
                 fmt::styled("TestBed::Init()",
                             fg_color_lavender | fmt::emphasis::italic));
    Level::Init();
    sprite_sheet.Load("tiles.png");
}

void TestBed::Tick(double delta) {
    Level::Tick(delta);
}

void TestBed::Render(sf::RenderTarget &target) {
    Level::Render(target);
    sprite_sheet.Render(target, {0.f, 0.f});
}
