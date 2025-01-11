//
// Created by Kurt Slagle on 12/29/24.
//

#include "Physics.h"

namespace {
    auto gravity = vec2d(0.0f, -9.81f);
}

void AssignBoundaries(float ww, float wh) {
    mvHit::wdwW = ww;
    mvHit::wdwH = wh;
    mvHit::wdwCf = 0.f;
}


void UpdateAllPhysics(std::vector<std::shared_ptr<mvHit> > &mvHits, std::vector<std::shared_ptr<lineSeg> > &lineSegs) {
    for (auto &hit: mvHits) {
        hit->update(1.f);
    }

    for (auto &seg: mvHits) {
        seg->update(1.f);
    }


    for (auto &seg: lineSegs) {
        for (auto &mvhit: mvHits) {
            seg->hit(*mvhit);
        }
    }

    for (auto &hit1: mvHits) {
        for (auto &hit2: mvHits) {
            if (hit1 == hit2)
                continue;

            hit1->hit(*hit2);
        }
    }
}


void SetGravity(const vec2d &grav) {
    gravity = grav;
}
