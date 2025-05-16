//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Events/EventHandler.h>
#include <MultiThreading/WorkerThread.h>
#include <Physics/Physics.h>
#include <Config/EngineConfig.h>
#include <Level/Level.h>
#include <Benchmarking/Benchmark.h>

class Editor;

class Engine {
    friend class Editor;
private:

    std::unique_ptr<sf::RenderWindow> window;
    EventHandler evtHandler;
    bool quit = false;
    EngineConfig config;
    std::shared_ptr<entt::meta_any> maybeLevelPtr;
    std::vector<std::shared_ptr<mvHit> > mvHits;
    std::vector<std::shared_ptr<lineSeg> > lineSegs;
    double lastFrameTime = 0.0;
    WorkerThread engineWorker{"EngineWorker"};

    Benchmark mainLoopBenchmark{"MainLoop"};

public:
    Engine() = default;

    ~Engine() = default;

    int Init();
    bool InitEditor();

    void LoadConfig(const std::string &filename);
    void InitLevel();
    void SaveConfig(const std::string &filename);
    void InitWindow();
    void InitEvents();
    void InitImGui();
    void InitGlobals();
    void InitReflection();

    int Run();

    void RequestQuit();

    void GameLoop();

    void CheckWorkerResults();

    void Tick(sf::Time delta);

    static std::vector<std::string> PossibleLevelFiles;
    static void CheckIndexedFiles(
        const std::vector<std::filesystem::path> &paths);


    void MakePhysicsObjects();


    void OnClosed(const sf::Event &event);
    void OnFocusGained(const sf::Event &event);
    void OnFocusLost(const sf::Event &event);
    void OnWindowResized(const sf::Event &event);

    void OnMouseMoved(const sf::Event &event);
    void OnMousePressed(const sf::Event &event);
    void OnMouseReleased(const sf::Event &event);
    void OnMouseEntered(const sf::Event &event);
    void OnMouseLeft(const sf::Event &event);
    void OnMouseWheelScrolled(const sf::Event &event);

    void OnTouchBegin(const sf::Event &event);
    void OnTouchEnd(const sf::Event &event);
    void OnTouchMove(const sf::Event &event);

    void OnKeyPressed(const sf::Event &event);
    void OnKeyReleased(const sf::Event &event);
    void OnTextEntered(const sf::Event &event);

    void OnJoystickButtonPressed(const sf::Event &event);
    void OnJoystickButtonReleased(const sf::Event &event);
    void OnJoystickConnected(const sf::Event &event);
    void OnJoystickDisconnected(const sf::Event &event);
    void OnJoystickMoved(const sf::Event &event);

    void OnSensorChanged(const sf::Event &event);
};
