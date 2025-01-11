//
// Created by Kurt Slagle on 12/29/24.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include "arcSeg.h"
#include "ball.h"
#include "ball_go.h"
#include "block.h"
#include "decayPolygon.h"
#include "expandPolygon.h"
#include "lineBumper.h"
#include "lineSeg.h"
#include "mvHit.h"
#include "pipeSeg.h"
#include "regPolygon.h"
#include "segHit.h"
#include "waveSeg.h"
#include "lineSegConveyor.h"
#include "lineSegElevator.h"
#include "lineSegFlip.h"
#include "lineSegRotate.h"
#include "lineSegSwing.h"

#include <bitflags/bitflags.hpp>
#include <vector>
#include <memory>

BEGIN_BITFLAGS(CollideGroup)
    FLAG(None)    // No collisions, can be used for other physics-related things
    FLAG(Bullets) // High-speed collisions, uses finer tracking
    FLAG(Particles)
    FLAG(Static) // Static geometry, optimized for little to no movement
    FLAG(Player) // Player group, isolate the player
    FLAG(ExtraGroup1)
    FLAG(ExtraGroup2)
    FLAG(ExtraGroup3)
    FLAG(ExtraGroup4)
END_BITFLAGS(CollideGroup)

void UpdateAllPhysics(std::vector<std::shared_ptr<mvHit> > &mvHits,
                      std::vector<std::shared_ptr<lineSeg> > &lineSegs);
void AssignBoundaries(float ww, float wh);
void SetGravity(const vec2d &grav);

#endif //PHYSICS_H
