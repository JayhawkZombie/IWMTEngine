//
// Created by Kurt Slagle on 1/3/25.
//

#include <Engine/Engine.h>

void Engine::OnClosed(const sf::Event &event) {
    RequestQuit();
}

void Engine::OnFocusGained(const sf::Event &event) {

}

void Engine::OnFocusLost(const sf::Event &event) {

}

void Engine::OnWindowResized(const sf::Event &event) {

}

void Engine::OnMouseMoved(const sf::Event &event) {
}

void Engine::OnMousePressed(const sf::Event &event) {
}

void Engine::OnMouseReleased(const sf::Event &event) {
}

void Engine::OnMouseEntered(const sf::Event &event) {

}

void Engine::OnMouseLeft(const sf::Event &event) {

}

void Engine::OnMouseWheelScrolled(const sf::Event &event) {

}

void Engine::OnTouchBegin(const sf::Event &event) {

}

void Engine::OnTouchEnd(const sf::Event &event) {

}

void Engine::OnTouchMove(const sf::Event &event) {

}

void Engine::OnKeyPressed(const sf::Event &event) {
    if (event.key.code == sf::Keyboard::Escape) {
        RequestQuit();
    }
}

void Engine::OnKeyReleased(const sf::Event &event) {
}

void Engine::OnTextEntered(const sf::Event &event) {

}

void Engine::OnJoystickButtonPressed(const sf::Event &event) {

}

void Engine::OnJoystickButtonReleased(const sf::Event &event) {

}

void Engine::OnJoystickConnected(const sf::Event &event) {

}

void Engine::OnJoystickDisconnected(const sf::Event &event) {

}

void Engine::OnJoystickMoved(const sf::Event &event) {

}

void Engine::OnSensorChanged(const sf::Event &event) {

}
