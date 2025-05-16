#pragma once
/**********************************
* GeneratedSerializationData.h
* Generated at: 15/05/2025 10:44:12
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
#include "../src/Level/LightMeUp/Light_types/LightPlayer2.h"
#include "../src/Engine/GameObject.h"
#include "../src/Editor/Editor.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <Serialization/SerializeTypes.h>
namespace cereal {

template<class Archive>
void serialize(Archive &ar, PhysicsConfig &val) {
    try {
        ar(cereal::make_nvp("gravity", val.gravity));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in PhysicsConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, WindowConfig &val) {
    try {
        ar(cereal::make_nvp("width", val.width));
ar(cereal::make_nvp("height", val.height));
ar(cereal::make_nvp("enableVSync", val.enableVSync));
ar(cereal::make_nvp("enableMsaa", val.enableMsaa));
ar(cereal::make_nvp("enableFullscreen", val.enableFullscreen));
ar(cereal::make_nvp("enableResize", val.enableResize));
ar(cereal::make_nvp("frameRate", val.frameRate));
ar(cereal::make_nvp("windowTitle", val.windowTitle));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in WindowConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, CoreConfig &val) {
    try {
        ar(cereal::make_nvp("defaultFont", val.defaultFont));
ar(cereal::make_nvp("startEditorPaused", val.startEditorPaused));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in CoreConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, GameInitConfig &val) {
    try {
        ar(cereal::make_nvp("levelName", val.levelName));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in GameInitConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, EngineConfig &val) {
    try {
        ar(cereal::make_nvp("core", val.core));
ar(cereal::make_nvp("window", val.window));
ar(cereal::make_nvp("physics", val.physics));
ar(cereal::make_nvp("game", val.game));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in EngineConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, Level &val) {
    try {
        ar(cereal::make_nvp("name", val.name));
ar(cereal::make_nvp("gameObjects", val.gameObjects));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in Level: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, TestBed &val) {
    try {
        
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in TestBed: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, SpriteSheet &val) {
    try {
        ar(cereal::make_nvp("originalFileName", val.originalFileName));
ar(cereal::make_nvp("dimensions", val.dimensions));
ar(cereal::make_nvp("rawFrames", val.rawFrames));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in SpriteSheet: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, TarmieLevel &val) {
    try {
        ar(cereal::make_nvp("m_spriteSheet", val.m_spriteSheet));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in TarmieLevel: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, LightMeUpLevel &val) {
    try {
        ar(cereal::make_nvp("m_matrixWidth", val.m_matrixWidth));
ar(cereal::make_nvp("m_matrixHeight", val.m_matrixHeight));
ar(cereal::make_nvp("m_boxSize", val.m_boxSize));
ar(cereal::make_nvp("m_boxSpacing", val.m_boxSpacing));
ar(cereal::make_nvp("m_boxPosition", val.m_boxPosition));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in LightMeUpLevel: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, InitPatternConfig &val) {
    try {
        ar(cereal::make_nvp("rows", val.rows));
ar(cereal::make_nvp("cols", val.cols));
ar(cereal::make_nvp("posX", val.posX));
ar(cereal::make_nvp("posY", val.posY));
ar(cereal::make_nvp("dPosX", val.dPosX));
ar(cereal::make_nvp("dPosY", val.dPosY));
ar(cereal::make_nvp("lightSize", val.lightSize));
ar(cereal::make_nvp("numPatterns", val.numPatterns));
ar(cereal::make_nvp("pd", val.pd));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in InitPatternConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, WavePlayerConfig &val) {
    try {
        ar(cereal::make_nvp("rows", val.rows));
ar(cereal::make_nvp("cols", val.cols));
ar(cereal::make_nvp("onLight", val.onLight));
ar(cereal::make_nvp("offLight", val.offLight));
ar(cereal::make_nvp("C_Rt", val.C_Rt));
ar(cereal::make_nvp("C_Lt", val.C_Lt));
ar(cereal::make_nvp("useRightCoefficients", val.useRightCoefficients));
ar(cereal::make_nvp("useLeftCoefficients", val.useLeftCoefficients));
ar(cereal::make_nvp("AmpLt", val.AmpLt));
ar(cereal::make_nvp("AmpRt", val.AmpRt));
ar(cereal::make_nvp("wvLenLt", val.wvLenLt));
ar(cereal::make_nvp("wvLenRt", val.wvLenRt));
ar(cereal::make_nvp("wvSpdLt", val.wvSpdLt));
ar(cereal::make_nvp("wvSpdRt", val.wvSpdRt));
ar(cereal::make_nvp("rightTrigFuncIndex", val.rightTrigFuncIndex));
ar(cereal::make_nvp("leftTrigFuncIndex", val.leftTrigFuncIndex));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in WavePlayerConfig: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, Light &val) {
    try {
        ar(cereal::make_nvp("r", val.r));
ar(cereal::make_nvp("g", val.g));
ar(cereal::make_nvp("b", val.b));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in Light: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, patternData &val) {
    try {
        ar(cereal::make_nvp("funcIndex", val.funcIndex));
ar(cereal::make_nvp("stepPause", val.stepPause));
ar(cereal::make_nvp("param", val.param));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in patternData: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, GameObject &val) {
    try {
        ar(cereal::make_nvp("position", val.position));
ar(cereal::make_nvp("size", val.size));
ar(cereal::make_nvp("awake", val.awake));
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in GameObject: " << e.what() << std::endl;
    }
}


template<class Archive>
void serialize(Archive &ar, Editor &val) {
    try {
        
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in Editor: " << e.what() << std::endl;
    }
}

}//namespace cereal
