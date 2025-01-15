//
// Created by Kurt Slagle on 12/31/24.
//

#include "EventHandler.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <fmt/format.h>
#include <Logging/LogFormatting.h>

void EventHandler::ProcessEvents(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(window, event);
        // fmt::println("Event: {}", event);

        if (event.type == sf::Event::KeyPressed) {
            KeyPressEventDispatcher.enqueue<sf::Event>(event);
        }else if (event.type == sf::Event::KeyReleased) {
            KeyReleaseEventDispatcher.enqueue<sf::Event>(event);
        }else if (event.type == sf::Event::Closed) {
            CloseEventDispatcher.enqueue<sf::Event>(event);
        }else if (event.type == sf::Event::MouseButtonPressed) {
            MousePressEventDispatcher.enqueue<sf::Event>(event);
        }else if (event.type == sf::Event::MouseButtonReleased) {
            MouseReleaseEventDispatcher.enqueue<sf::Event>(event);
        }else if (event.type == sf::Event::MouseMoved) {
            MouseMoveEventDispatcher.enqueue<sf::Event>(event);
        }

        KeyPressEventDispatcher.update<sf::Event>();
        KeyReleaseEventDispatcher.update<sf::Event>();
        CloseEventDispatcher.update<sf::Event>();
        MouseMoveEventDispatcher.update<sf::Event>();
        MousePressEventDispatcher.update<sf::Event>();
        MouseReleaseEventDispatcher.update<sf::Event>();
    }
}
