/**********************************
* GeneratedReflectionData.cpp
* Generated at: 03/04/2025 16:45:02
*/


    #include <Globals.h>
    #include <Logging/Logging.h>
#include "../src/Config/EngineConfig.h"
#include "../src/Level/Level.h"
#include "../src/Level/TestBed.h"
#include "../src/Level/TestBed/SpriteSheet.h"
#include "../src/Level/Tarmie/TarmieLevel.h"
#include "../src/Level/LightMeUp/LightMeUpLevel.h"
#include "../src/Level/LightMeUp/LightVisual.h"
#include "../src/Engine/GameObject.h"


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
            
            GlobalConsole->Debug("Registering LightMeUpLevel m_visual visual");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_visual>(\"visual\"_hs);");
            rFactory.data<&LightMeUpLevel::m_visual>("visual"_hs);
        
	
            GlobalConsole->Debug("Registering LightMeUpLevel m_matrixHeight height");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightMeUpLevel::m_matrixHeight>(\"height\"_hs);");
            rFactory.data<&LightMeUpLevel::m_matrixHeight>("height"_hs);
        
        }
    

        void Reflect_LightVisual() {
            std::cerr << "	Registering class LightVisual" << std::endl;
            using namespace entt::literals;
auto rFactory = entt::meta<LightVisual>();
rFactory.ctor<>();
            
            
            GlobalConsole->Debug("Registering LightVisual numLts numLights");
            GlobalConsole->Debug("	Code string: rFactory.data<&LightVisual::numLts>(\"numLights\"_hs);");
            rFactory.data<&LightVisual::numLts>("numLights"_hs);
        
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
	Reflect_LightVisual();
	Reflect_GameObject();
        }
    