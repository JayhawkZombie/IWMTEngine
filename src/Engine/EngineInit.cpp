//
// Created by Kurt Slagle on 12/31/24.
//

#include <Globals.h>
#include <Engine/Engine.h>
#include <Physics/Physics.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Misc/IconsFontAwesome6.h>
#include <Timing/TimerManager.h>
#include <Console/EngineConsole.h>
#include <Logging/LogFormatting.h>
#include <Misc/IniConfig.h>
#include <cereal/archives/json.hpp>
#include <GeneratedSerializationData.h>
#include <Level/Level.h>
#include <MultiThreading/Tasks/LevelMakerTask.h>
#include <Reflection/Reflection.h>

vec2d gravity = vec2d(0, 9.81f);

void Engine::LoadConfig(const std::string &filename) {
    {
        std::ifstream configFile(filename);
        if (!configFile) {
            fmt::println("Failed to open config file {}",
                         fmt::styled(filename, fg_color_green));
            fmt::println("Creating config file {}",
                         fmt::styled(filename, fg_color_green));
            SaveConfig(filename);
            return;
        }
        cereal::JSONInputArchive inArchive(configFile);
        inArchive(cereal::make_nvp("engineConfig", config));
        gravity = config.physics.gravity;
    }
}

void Engine::InitLevel() {
    engineWorker.PostTask(LevelMakerTask{config.game.levelName}, "LevelMaker");
}

void Engine::SaveConfig(const std::string &filename) {
    {
        std::ofstream configFile(filename);
        if (!configFile) {
            fmt::println("Failed to open config file for writing {}",
                         fmt::styled(filename, fg_color_green));
            return;
        }

        cereal::JSONOutputArchive outArchive(configFile);
        outArchive(cereal::make_nvp("engineConfig", config));
    }
}

void Engine::InitWindow() {
    sf::VideoMode vMode;
    vMode.width  = config.window.width;
    vMode.height = config.window.height;

    sf::Uint32 wStyle = sf::Style::Default;
    if (config.window.enableFullscreen) {
        wStyle |= sf::Style::Fullscreen;
    }

    sf::ContextSettings ctxSettings;
    ctxSettings.antialiasingLevel = config.window.enableMsaa ? 4 : 0;
    window                        = std::make_unique<sf::RenderWindow>(vMode,
        config.window.windowTitle,
        wStyle,
        ctxSettings);
    window->setFramerateLimit(config.window.frameRate);
}

void Engine::InitEvents() {
    evtHandler.CloseEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnClosed>(this);
    evtHandler.FocusGainedEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnFocusGained>(this);
    evtHandler.FocusLostEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnFocusLost>(this);
    evtHandler.WindowResizedEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnWindowResized>(this);

    evtHandler.MouseMoveEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMouseMoved>(this);
    evtHandler.MousePressEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMousePressed>(this);
    evtHandler.MouseReleaseEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMouseReleased>(this);
    evtHandler.MouseEnteredEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMouseEntered>(this);
    evtHandler.MouseLeftEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMouseLeft>(this);
    evtHandler.MouseWheelScrolledEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnMouseWheelScrolled>(this);

    evtHandler.TouchBeginEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnTouchBegin>(this);
    evtHandler.TouchEndEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnTouchEnd>(this);
    evtHandler.TouchMovedEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnTouchMove>(this);

    evtHandler.KeyPressEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnKeyPressed>(this);
    evtHandler.KeyReleaseEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnKeyReleased>(this);
    evtHandler.TextEnteredEventDispatcher.sink<sf::Event>().connect<&
        Engine::OnTextEntered>(this);
}

void Engine::InitImGui() {
    const auto fontName = std::string("Ubuntu-R.ttf");
    auto &io            = ImGui::GetIO();
    io.Fonts->Clear();
    // clear fonts if you loaded some before (even if only default one was loaded)
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.Fonts->AddFontDefault();
    float baseFontSize                     = 13.f;
    float iconBaseSize                     = baseFontSize * 2.f / 3.f;
    static constexpr ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode        = true;
    icons_config.PixelSnapH       = true;
    icons_config.GlyphMinAdvanceX = iconBaseSize;
    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS,
                                 iconBaseSize,
                                 &icons_config,
                                 icon_ranges);
    auto *font = io.Fonts->AddFontFromFileTTF(fontName.c_str(),
                                              12.f,
                                              nullptr,
                                              io.Fonts->
                                                 GetGlyphRangesDefault());
    IM_ASSERT(font != nullptr);
    if (!ImGui::SFML::UpdateFontTexture()) {
        fmt::println("{}",
                     fmt::styled("Failed to update font texture!",
                                 fg_color_red));
    }
}

void Engine::InitGlobals() {
    GlobalTimerManager = std::make_unique<TimerManager>();
    GlobalTimerManager->Init();
    GlobalConsole = std::make_unique<EngineConsole>();
    GlobalConsole->Init();
    GlobalIniConfig = std::make_unique<IniConfig>();
    GlobalIniConfig->Read("config.ini");
    GlobalIniConfig->Print(std::cout);
}

void Engine::InitReflection() {
    using namespace entt::literals;
    entt::meta_reset();
    entt::meta<vec2d>().ctor<>().data<&vec2d::x>("x"_hs).data<&
        vec2d::y>("y"_hs);
    // entt::meta<Level>().ctor<>().type("Level"_hs).data<&Level::name>("name"_hs);
    Reflect_RegisterAll();
}


int Engine::Init() {
    InitGlobals();
    LoadConfig("config.json");
    InitReflection();
    InitWindow();
    InitEvents();
    InitLevel();

    GlobalTimerManager->AddTimer(5.0,
                                 false,
                                 []() {
                                     std::cerr << "Timer expired!" << std::endl;
                                 });

    // MakePhysicsObjects();
    SetGravity(gravity);
    AssignBoundaries(config.window.width, config.window.height);

    if (!ImGui::SFML::Init(*window)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }
    InitImGui();

    return 0;
}
