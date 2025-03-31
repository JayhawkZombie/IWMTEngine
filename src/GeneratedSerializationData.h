#pragma once
/**********************************
* GeneratedSerializationData.h
* Generated at: 30/03/2025 19:20:43
*/


    #include <Globals.h>
    #include <Logging/Logging.h>
#include "../src/Config/EngineConfig.h"
#include "../src/Level/Level.h"
#include "../src/Level/TestBed.h"
#include "../src/Level/TestBed/SpriteSheet.h"
#include "../src/Level/Tarmie/TarmieLevel.h"
#include "../src/Level/LightMeUp/LightMeUpLevel.h"
#include "../src/Level/LightMeUp/StarrySky.h"
#include "../src/Level/LightMeUp/PatternPlayer.h"
#include "../src/Level/LightMeUp/LightVisual.h"
#include "../src/Engine/GameObject.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
namespace cereal {

template<class Archive>
void serialize(Archive &ar, PhysicsConfig &val) {
    ar(cereal::make_nvp("gravity", val.gravity));
}


template<class Archive>
void serialize(Archive &ar, WindowConfig &val) {
    ar(cereal::make_nvp("width", val.width));
ar(cereal::make_nvp("height", val.height));
ar(cereal::make_nvp("enableVSync", val.enableVSync));
ar(cereal::make_nvp("enableMsaa", val.enableMsaa));
ar(cereal::make_nvp("enableFullscreen", val.enableFullscreen));
ar(cereal::make_nvp("enableResize", val.enableResize));
ar(cereal::make_nvp("frameRate", val.frameRate));
ar(cereal::make_nvp("windowTitle", val.windowTitle));
}


template<class Archive>
void serialize(Archive &ar, CoreConfig &val) {
    ar(cereal::make_nvp("defaultFont", val.defaultFont));
ar(cereal::make_nvp("startEditorPaused", val.startEditorPaused));
}


template<class Archive>
void serialize(Archive &ar, GameInitConfig &val) {
    ar(cereal::make_nvp("levelName", val.levelName));
}


template<class Archive>
void serialize(Archive &ar, EngineConfig &val) {
    ar(cereal::make_nvp("core", val.core));
ar(cereal::make_nvp("window", val.window));
ar(cereal::make_nvp("physics", val.physics));
ar(cereal::make_nvp("game", val.game));
}


template<class Archive>
void serialize(Archive &ar, Level &val) {
    ar(cereal::make_nvp("name", val.name));
ar(cereal::make_nvp("gameObjects", val.gameObjects));
}


template<class Archive>
void serialize(Archive &ar, TestBed &val) {
    
}


template<class Archive>
void serialize(Archive &ar, SpriteSheet &val) {
    ar(cereal::make_nvp("originalFileName", val.originalFileName));
ar(cereal::make_nvp("dimensions", val.dimensions));
ar(cereal::make_nvp("rawFrames", val.rawFrames));
}


template<class Archive>
void serialize(Archive &ar, TarmieLevel &val) {
    ar(cereal::make_nvp("m_spriteSheet", val.m_spriteSheet));
}


template<class Archive>
void serialize(Archive &ar, LightMeUpLevel &val) {
    ar(cereal::make_nvp("m_visual", val.m_visual));
ar(cereal::make_nvp("m_matrixHeight", val.m_matrixHeight));
}


template<class Archive>
void serialize(Archive &ar, Star &val) {
    ar(cereal::make_nvp("position", val.position));
ar(cereal::make_nvp("brightness", val.brightness));
ar(cereal::make_nvp("size", val.size));
}


template<class Archive>
void serialize(Archive &ar, Cell &val) {
    ar(cereal::make_nvp("stars", val.stars));
ar(cereal::make_nvp("visibility", val.visibility));
ar(cereal::make_nvp("color", val.color));
}


template<class Archive>
void serialize(Archive &ar, StarrySky &val) {
    ar(cereal::make_nvp("m_grid", val.m_grid));
ar(cereal::make_nvp("m_rng", val.m_rng));
ar(cereal::make_nvp("m_backgroundColor", val.m_backgroundColor));
}


template<class Archive>
void serialize(Archive &ar, PatternPlayer &val) {
    ar(cereal::make_nvp("m_patterns", val.m_patterns));
ar(cereal::make_nvp("m_onColor", val.m_onColor));
ar(cereal::make_nvp("m_offColor", val.m_offColor));
ar(cereal::make_nvp("m_accumulator", val.m_accumulator));
ar(cereal::make_nvp("m_speed", val.m_speed));
ar(cereal::make_nvp("m_rows", val.m_rows));
ar(cereal::make_nvp("m_cols", val.m_cols));
}


template<class Archive>
void serialize(Archive &ar, LightVisual &val) {
    ar(cereal::make_nvp("numLts", val.numLts));
}


template<class Archive>
void serialize(Archive &ar, GameObject &val) {
    ar(cereal::make_nvp("position", val.position));
ar(cereal::make_nvp("size", val.size));
ar(cereal::make_nvp("awake", val.awake));
}

}//namespace cereal
