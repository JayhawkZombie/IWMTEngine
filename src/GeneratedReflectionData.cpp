/**********************************
* GeneratedReflectionData.cpp
* Generated at: 14/05/2025 11:24:10
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


        void Reflect_PhysicsConfig() {
            std::cerr << "	Registering class PhysicsConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<PhysicsConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering vec2d gravity gravity");
            GlobalConsole->Debug("	Code string: rFactory.data<&PhysicsConfig::gravity>(\"gravity\"_hs);");
            rFactory.data<&PhysicsConfig::gravity>("gravity"_hs);
        
        }
    

        void Reflect_WindowConfig() {
            std::cerr << "	Registering class WindowConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<WindowConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering int width width");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::width>(\"width\"_hs);");
            rFactory.data<&WindowConfig::width>("width"_hs);
        
	
            GlobalConsole->Debug("Registering int height height");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::height>(\"height\"_hs);");
            rFactory.data<&WindowConfig::height>("height"_hs);
        
	
            GlobalConsole->Debug("Registering bool enableVSync enableVSync");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::enableVSync>(\"enableVSync\"_hs);");
            rFactory.data<&WindowConfig::enableVSync>("enableVSync"_hs);
        
	
            GlobalConsole->Debug("Registering bool enableMsaa enableMsaa");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::enableMsaa>(\"enableMsaa\"_hs);");
            rFactory.data<&WindowConfig::enableMsaa>("enableMsaa"_hs);
        
	
            GlobalConsole->Debug("Registering bool enableFullscreen enableFullscreen");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::enableFullscreen>(\"enableFullscreen\"_hs);");
            rFactory.data<&WindowConfig::enableFullscreen>("enableFullscreen"_hs);
        
	
            GlobalConsole->Debug("Registering bool enableResize enableResize");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::enableResize>(\"enableResize\"_hs);");
            rFactory.data<&WindowConfig::enableResize>("enableResize"_hs);
        
	
            GlobalConsole->Debug("Registering int frameRate frameRate");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::frameRate>(\"frameRate\"_hs);");
            rFactory.data<&WindowConfig::frameRate>("frameRate"_hs);
        
	
            GlobalConsole->Debug("Registering bool windowTitle windowTitle");
            GlobalConsole->Debug("	Code string: rFactory.data<&WindowConfig::windowTitle>(\"windowTitle\"_hs);");
            rFactory.data<&WindowConfig::windowTitle>("windowTitle"_hs);
        
        }
    

        void Reflect_CoreConfig() {
            std::cerr << "	Registering class CoreConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<CoreConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering std::string defaultFont defaultFont");
            GlobalConsole->Debug("	Code string: rFactory.data<&CoreConfig::defaultFont>(\"defaultFont\"_hs);");
            rFactory.data<&CoreConfig::defaultFont>("defaultFont"_hs);
        
	
            GlobalConsole->Debug("Registering bool startEditorPaused startEditorPaused");
            GlobalConsole->Debug("	Code string: rFactory.data<&CoreConfig::startEditorPaused>(\"startEditorPaused\"_hs);");
            rFactory.data<&CoreConfig::startEditorPaused>("startEditorPaused"_hs);
        
        }
    

        void Reflect_GameInitConfig() {
            std::cerr << "	Registering class GameInitConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<GameInitConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering std::string levelName levelName");
            GlobalConsole->Debug("	Code string: rFactory.data<&GameInitConfig::levelName>(\"levelName\"_hs);");
            rFactory.data<&GameInitConfig::levelName>("levelName"_hs);
        
        }
    

        void Reflect_EngineConfig() {
            std::cerr << "	Registering class EngineConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<EngineConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering EngineConfig core core");
            GlobalConsole->Debug("	Code string: rFactory.data<&EngineConfig::core>(\"core\"_hs);");
            rFactory.data<&EngineConfig::core>("core"_hs);
        
	
            GlobalConsole->Debug("Registering EngineConfig window window");
            GlobalConsole->Debug("	Code string: rFactory.data<&EngineConfig::window>(\"window\"_hs);");
            rFactory.data<&EngineConfig::window>("window"_hs);
        
	
            GlobalConsole->Debug("Registering EngineConfig physics physics");
            GlobalConsole->Debug("	Code string: rFactory.data<&EngineConfig::physics>(\"physics\"_hs);");
            rFactory.data<&EngineConfig::physics>("physics"_hs);
        
	
            GlobalConsole->Debug("Registering EngineConfig game game");
            GlobalConsole->Debug("	Code string: rFactory.data<&EngineConfig::game>(\"game\"_hs);");
            rFactory.data<&EngineConfig::game>("game"_hs);
        
        }
    

        void Reflect_Level() {
            std::cerr << "	Registering class Level" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<Level>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering std::string name name");
            GlobalConsole->Debug("	Code string: rFactory.data<&Level::name>(\"name\"_hs);");
            rFactory.data<&Level::name>("name"_hs);
        
	
            GlobalConsole->Debug("Registering std::vector<std::shared_ptr<GameObject>> gameObjects gameObjects");
            GlobalConsole->Debug("	Code string: rFactory.data<&Level::gameObjects>(\"gameObjects\"_hs);");
            rFactory.data<&Level::gameObjects>("gameObjects"_hs);
        
        }
    

        void Reflect_TestBed() {
            std::cerr << "	Registering class TestBed" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<TestBed>();
            rFactory.ctor<>();
            rFactory.base<Level>();
            
        }
    

        void Reflect_SpriteSheet() {
            std::cerr << "	Registering class SpriteSheet" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<SpriteSheet>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering std::string originalFileName originalFileName");
            GlobalConsole->Debug("	Code string: rFactory.data<&SpriteSheet::originalFileName>(\"originalFileName\"_hs);");
            rFactory.data<&SpriteSheet::originalFileName>("originalFileName"_hs);
        
	
            GlobalConsole->Debug("Registering sf::IntRect dimensions dimensions");
            GlobalConsole->Debug("	Code string: rFactory.data<&SpriteSheet::dimensions>(\"dimensions\"_hs);");
            rFactory.data<&SpriteSheet::dimensions>("dimensions"_hs);
        
	
            GlobalConsole->Debug("Registering std::vector<sf::IntRect> rawFrames rawFrames");
            GlobalConsole->Debug("	Code string: rFactory.data<&SpriteSheet::rawFrames>(\"rawFrames\"_hs);");
            rFactory.data<&SpriteSheet::rawFrames>("rawFrames"_hs);
        
        }
    

        void Reflect_TarmieLevel() {
            std::cerr << "	Registering class TarmieLevel" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<TarmieLevel>();
            rFactory.ctor<>();
            rFactory.base<Level>();
            
            GlobalConsole->Debug("Registering SpriteSheet m_spriteSheet spriteSheet");
            GlobalConsole->Debug("	Code string: rFactory.data<&TarmieLevel::m_spriteSheet>(\"spriteSheet\"_hs);");
            rFactory.data<&TarmieLevel::m_spriteSheet>("spriteSheet"_hs);
        
        }
    

        void Reflect_LightMeUpLevel() {
            std::cerr << "	Registering class LightMeUpLevel" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<LightMeUpLevel>();
            rFactory.ctor<>();
            rFactory.base<Level>();
            
            GlobalConsole->Debug("Registering LightMeUpLevel m_matrixWidth width");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_matrixWidth>(\"width\"_hs);");
            rFactory.data<&LightMeUpLevel::m_matrixWidth>("width"_hs);
        
	
            GlobalConsole->Debug("Registering LightMeUpLevel m_matrixHeight height");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_matrixHeight>(\"height\"_hs);");
            rFactory.data<&LightMeUpLevel::m_matrixHeight>("height"_hs);
        
	
            GlobalConsole->Debug("Registering LightMeUpLevel m_boxSize boxSize");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_boxSize>(\"boxSize\"_hs);");
            rFactory.data<&LightMeUpLevel::m_boxSize>("boxSize"_hs);
        
	
            GlobalConsole->Debug("Registering LightMeUpLevel m_boxSpacing boxSpacing");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_boxSpacing>(\"boxSpacing\"_hs);");
            rFactory.data<&LightMeUpLevel::m_boxSpacing>("boxSpacing"_hs);
        
	
            GlobalConsole->Debug("Registering LightMeUpLevel m_boxPosition boxPosition");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_boxPosition>(\"boxPosition\"_hs);");
            rFactory.data<&LightMeUpLevel::m_boxPosition>("boxPosition"_hs);
        
        }
    

        void Reflect_InitPatternConfig() {
            std::cerr << "	Registering class InitPatternConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<InitPatternConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering InitPatternConfig rows rows");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::rows>(\"rows\"_hs);");
            rFactory.data<&InitPatternConfig::rows>("rows"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig cols cols");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::cols>(\"cols\"_hs);");
            rFactory.data<&InitPatternConfig::cols>("cols"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig posX posX");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::posX>(\"posX\"_hs);");
            rFactory.data<&InitPatternConfig::posX>("posX"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig posY posY");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::posY>(\"posY\"_hs);");
            rFactory.data<&InitPatternConfig::posY>("posY"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig dPosX dPosX");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::dPosX>(\"dPosX\"_hs);");
            rFactory.data<&InitPatternConfig::dPosX>("dPosX"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig dPosY dPosY");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::dPosY>(\"dPosY\"_hs);");
            rFactory.data<&InitPatternConfig::dPosY>("dPosY"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig lightSize lightSize");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::lightSize>(\"lightSize\"_hs);");
            rFactory.data<&InitPatternConfig::lightSize>("lightSize"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig numPatterns numPatterns");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::numPatterns>(\"numPatterns\"_hs);");
            rFactory.data<&InitPatternConfig::numPatterns>("numPatterns"_hs);
        
	
            GlobalConsole->Debug("Registering InitPatternConfig pd pd");
            GlobalConsole->Debug("	Code string: rFactory.data<&InitPatternConfig::pd>(\"pd\"_hs);");
            rFactory.data<&InitPatternConfig::pd>("pd"_hs);
        
        }
    

        void Reflect_WavePlayerConfig() {
            std::cerr << "	Registering class WavePlayerConfig" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<WavePlayerConfig>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering WavePlayerConfig rows rows");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::rows>(\"rows\"_hs);");
            rFactory.data<&WavePlayerConfig::rows>("rows"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig cols cols");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::cols>(\"cols\"_hs);");
            rFactory.data<&WavePlayerConfig::cols>("cols"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig onLight onLight");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::onLight>(\"onLight\"_hs);");
            rFactory.data<&WavePlayerConfig::onLight>("onLight"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig offLight offLight");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::offLight>(\"offLight\"_hs);");
            rFactory.data<&WavePlayerConfig::offLight>("offLight"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig C_Rt C_Rt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::C_Rt>(\"C_Rt\"_hs);");
            rFactory.data<&WavePlayerConfig::C_Rt>("C_Rt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig C_Lt C_Lt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::C_Lt>(\"C_Lt\"_hs);");
            rFactory.data<&WavePlayerConfig::C_Lt>("C_Lt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig useRightCoefficients useRightCoefficients");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::useRightCoefficients>(\"useRightCoefficients\"_hs);");
            rFactory.data<&WavePlayerConfig::useRightCoefficients>("useRightCoefficients"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig useLeftCoefficients useLeftCoefficients");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::useLeftCoefficients>(\"useLeftCoefficients\"_hs);");
            rFactory.data<&WavePlayerConfig::useLeftCoefficients>("useLeftCoefficients"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig AmpLt AmpLt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::AmpLt>(\"AmpLt\"_hs);");
            rFactory.data<&WavePlayerConfig::AmpLt>("AmpLt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig AmpRt AmpRt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::AmpRt>(\"AmpRt\"_hs);");
            rFactory.data<&WavePlayerConfig::AmpRt>("AmpRt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig wvLenLt wvLenLt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::wvLenLt>(\"wvLenLt\"_hs);");
            rFactory.data<&WavePlayerConfig::wvLenLt>("wvLenLt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig wvLenRt wvLenRt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::wvLenRt>(\"wvLenRt\"_hs);");
            rFactory.data<&WavePlayerConfig::wvLenRt>("wvLenRt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig wvSpdLt wvSpdLt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::wvSpdLt>(\"wvSpdLt\"_hs);");
            rFactory.data<&WavePlayerConfig::wvSpdLt>("wvSpdLt"_hs);
        
	
            GlobalConsole->Debug("Registering WavePlayerConfig wvSpdRt wvSpdRt");
            GlobalConsole->Debug("	Code string: rFactory.data<&WavePlayerConfig::wvSpdRt>(\"wvSpdRt\"_hs);");
            rFactory.data<&WavePlayerConfig::wvSpdRt>("wvSpdRt"_hs);
        
        }
    

        void Reflect_Light() {
            std::cerr << "	Registering class Light" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<Light>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering Light r r");
            GlobalConsole->Debug("	Code string: rFactory.data<&Light::r>(\"r\"_hs);");
            rFactory.data<&Light::r>("r"_hs);
        
	
            GlobalConsole->Debug("Registering Light g g");
            GlobalConsole->Debug("	Code string: rFactory.data<&Light::g>(\"g\"_hs);");
            rFactory.data<&Light::g>("g"_hs);
        
	
            GlobalConsole->Debug("Registering Light b b");
            GlobalConsole->Debug("	Code string: rFactory.data<&Light::b>(\"b\"_hs);");
            rFactory.data<&Light::b>("b"_hs);
        
        }
    

        void Reflect_patternData() {
            std::cerr << "	Registering class patternData" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<patternData>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering funcIndex funcIndex funcIndex");
            GlobalConsole->Debug("	Code string: rFactory.data<&patternData::funcIndex>(\"funcIndex\"_hs);");
            rFactory.data<&patternData::funcIndex>("funcIndex"_hs);
        
	
            GlobalConsole->Debug("Registering stepPause stepPause stepPause");
            GlobalConsole->Debug("	Code string: rFactory.data<&patternData::stepPause>(\"stepPause\"_hs);");
            rFactory.data<&patternData::stepPause>("stepPause"_hs);
        
	
            GlobalConsole->Debug("Registering param param param");
            GlobalConsole->Debug("	Code string: rFactory.data<&patternData::param>(\"param\"_hs);");
            rFactory.data<&patternData::param>("param"_hs);
        
        }
    

        void Reflect_GameObject() {
            std::cerr << "	Registering class GameObject" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<GameObject>();
            rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering sf::Vector2 position position");
            GlobalConsole->Debug("	Code string: rFactory.data<&GameObject::position>(\"position\"_hs);");
            rFactory.data<&GameObject::position>("position"_hs);
        
	
            GlobalConsole->Debug("Registering sf::Vector2 size size");
            GlobalConsole->Debug("	Code string: rFactory.data<&GameObject::size>(\"size\"_hs);");
            rFactory.data<&GameObject::size>("size"_hs);
        
	
            GlobalConsole->Debug("Registering bool awake awake");
            GlobalConsole->Debug("	Code string: rFactory.data<&GameObject::awake>(\"awake\"_hs);");
            rFactory.data<&GameObject::awake>("awake"_hs);
        
        }
    

        void Reflect_Editor() {
            std::cerr << "	Registering class Editor" << std::endl;
            using namespace entt::literals;
            auto rFactory = entt::meta<Editor>();
            rFactory.ctor<>();
            
            
        }
    

        void Reflect_RegisterAll() {
            std::cerr << "Registering all reflection classes" << std::endl;
            Reflect_PhysicsConfig();
	Reflect_WindowConfig();
	Reflect_CoreConfig();
	Reflect_GameInitConfig();
	Reflect_EngineConfig();
	Reflect_Level();
	Reflect_TestBed();
	Reflect_SpriteSheet();
	Reflect_TarmieLevel();
	Reflect_LightMeUpLevel();
	Reflect_InitPatternConfig();
	Reflect_WavePlayerConfig();
	Reflect_Light();
	Reflect_patternData();
	Reflect_GameObject();
	Reflect_Editor();
        }
    