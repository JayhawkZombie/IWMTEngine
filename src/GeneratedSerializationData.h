#pragma once
/**********************************
* GeneratedSerializationData.h
* Generated at: 27/04/2025 08:07:51
*/


    #include <Globals.h>
    #include <Logging/Logging.h>
#include "../src/Config/EngineConfig.h"
#include "../src/Level/Level.h"
#include "../src/Level/TestBed.h"
#include "../src/Level/TestBed/SpriteSheet.h"
#include "../src/Level/Tarmie/TarmieLevel.h"
#include "../src/Level/LightMeUp/LightMeUpLevel.h"
#include "../src/Level/LightMeUp/WavePlayerWrapper.h"
#include "../src/Level/LightMeUp/Light_types/Light.h"
#include "../src/Engine/GameObject.h"
#include "../src/Editor/Editor.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <Serialization/SerializeTypes.h>
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
    ar(cereal::make_nvp("m_matrixWidth", val.m_matrixWidth));
ar(cereal::make_nvp("m_matrixHeight", val.m_matrixHeight));
ar(cereal::make_nvp("m_boxSize", val.m_boxSize));
ar(cereal::make_nvp("m_boxSpacing", val.m_boxSpacing));
ar(cereal::make_nvp("m_boxPosition", val.m_boxPosition));
}


template<class Archive>
void serialize(Archive &ar, WavePlayerConfig &val) {
    ar(cereal::make_nvp("rows", val.rows));
ar(cereal::make_nvp("cols", val.cols));
ar(cereal::make_nvp("onLight", val.onLight));
ar(cereal::make_nvp("offLight", val.offLight));
ar(cereal::make_nvp("C_Rt", val.C_Rt));
ar(cereal::make_nvp("AmpLt", val.AmpLt));
ar(cereal::make_nvp("AmpRt", val.AmpRt));
ar(cereal::make_nvp("wvLenLt", val.wvLenLt));
ar(cereal::make_nvp("wvLenRt", val.wvLenRt));
ar(cereal::make_nvp("wvSpdLt", val.wvSpdLt));
ar(cereal::make_nvp("wvSpdRt", val.wvSpdRt));
}


template<class Archive>
void serialize(Archive &ar, Light &val) {
    ar(cereal::make_nvp("r", val.r));
ar(cereal::make_nvp("g", val.g));
ar(cereal::make_nvp("b", val.b));
}


template<class Archive>
void serialize(Archive &ar, GameObject &val) {
    ar(cereal::make_nvp("position", val.position));
ar(cereal::make_nvp("size", val.size));
ar(cereal::make_nvp("awake", val.awake));
}


template<class Archive>
void serialize(Archive &ar, Editor &val) {
    
}

}//namespace cereal
