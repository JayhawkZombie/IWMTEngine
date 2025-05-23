//
// Created by Kurt Slagle on 12/31/24.
//

#include <Engine/Engine.h>
#include <Editor/Editor.h>
#include <Globals.h>
#include <Timing/TimerManager.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Console/EngineConsole.h>
#include <Misc/IconsFontAwesome6.h>

void Engine::GameLoop() {
    sf::Event event{};
    sf::Clock deltaClock;
    WorkerThread::Heartbeat lastHeartbeat;
    std::chrono::steady_clock::duration lastHbDelta{0};

    const auto AddJitterTask = [&]() {
        engineWorker.PostTask([]() {
                                  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                  return std::make_shared<
                                      entt::meta_any>(nullptr);
                              },
                              "Jitter Task");
    };

    Benchmark::benchmark_duration_t last_main_loop_duration{0};
    while (!quit) {
        mainLoopBenchmark.Start();
        CheckWorkerResults();
        const auto delta       = deltaClock.restart();
        Level *currentLevelPtr = maybeLevelPtr
                                     ? maybeLevelPtr->try_cast<Level>()
                                     : nullptr;
        if (!currentLevelPtr) {
            std::cerr << "Bad level ptr" << std::endl;
        }

        if (currentLevelPtr && !currentLevelPtr->IsInitialized()) {
            currentLevelPtr->Init();
        }

        evtHandler.ProcessEvents(*window);

        UpdateAllPhysics(mvHits, lineSegs);

        ImGui::SFML::Update(*window, delta);

        ImGui::Begin("IMWMTEngine" ICON_FA_PLAY);
        // Display the level dropdown
        GlobalEditor->DisplayLevelDropdown();
        if (ImGui::Button("Jitter worker")) {
            AddJitterTask();
        }
        WorkerThread::Heartbeat thisHeartbeat;
        const auto hbDelta = thisHeartbeat.time - lastHeartbeat.time;
        ImGui::Text("Last heartbeat delta %lld", hbDelta.count());
        if (engineWorker.TryGetLastHeartbeat(thisHeartbeat)) {
            lastHeartbeat = thisHeartbeat;
        }
        ImGui::Text("Last update %llu", last_main_loop_duration.count());
        ImGui::End();


        Tick(delta);
        if (currentLevelPtr) {
            currentLevelPtr->Tick((double) delta.asSeconds());
        }

        window->clear(sf::Color::White);

        if (currentLevelPtr) {
            currentLevelPtr->Render(*window);
        }

        for (const auto &mHit: mvHits) {
            mHit->draw(*window);
        }
        for (const auto &mLine: lineSegs) {
            mLine->draw(*window);
        }

        GlobalConsole->Render(*window);
        ImGui::ShowDemoWindow();

        if (currentLevelPtr) {
            currentLevelPtr->RenderEditor();
        }

        ImGui::SFML::Render(*window);
        window->display();
        mainLoopBenchmark.Stop();
        last_main_loop_duration = mainLoopBenchmark.GetDuration();
    }
    ImGui::SFML::Shutdown();
}




void Engine::Tick(sf::Time delta) {
    GlobalTimerManager->Tick((double) delta.asSeconds());
}
