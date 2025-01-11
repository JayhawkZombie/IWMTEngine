//
// Created by Kurt Slagle on 12/31/24.
//
#include <Engine/Engine.h>

void Engine::MakePhysicsObjects() {
    mvHits.clear();
    for (int i = 0; i < 10; i++) {
        auto ballPtr = std::make_shared<ball>();
        ballPtr->init(vec2d(i * 50.f, 50.f), vec2d(10.f, 10.f), 10.f, 1.f, 1.f);
        mvHits.push_back(ballPtr);
    }

    lineSegs.clear();
    for (int i = 0; i < 2; i++) {
        auto lSeg = std::make_shared<lineSeg>();
        lSeg->init(vec2d(100.f * i + 100.f, 200.f), vec2d(100.f * i + 150.f));
        lineSegs.push_back(lSeg);
    }
}
