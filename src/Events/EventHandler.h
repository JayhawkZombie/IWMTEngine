//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>


class EventHandler {
private:


public:
    /**
     * Window-related events
     */
    entt::dispatcher CloseEventDispatcher;
    entt::dispatcher FocusGainedEventDispatcher;
    entt::dispatcher FocusLostEventDispatcher;
    entt::dispatcher WindowResizedEventDispatcher;

    /**
     * Mouse-related events
     */
    entt::dispatcher MouseMoveEventDispatcher;
    entt::dispatcher MousePressEventDispatcher;
    entt::dispatcher MouseReleaseEventDispatcher;
    entt::dispatcher MouseEnteredEventDispatcher;
    entt::dispatcher MouseLeftEventDispatcher;
    entt::dispatcher MouseWheelScrolledEventDispatcher;

    /**
     * Touch/toucbpad-related events
     */
    entt::dispatcher TouchBeginEventDispatcher;
    entt::dispatcher TouchEndEventDispatcher;
    entt::dispatcher TouchMovedEventDispatcher;

    /**
     * Keyboard-related events
     */
    entt::dispatcher KeyPressEventDispatcher;
    entt::dispatcher KeyReleaseEventDispatcher;
    entt::dispatcher TextEnteredEventDispatcher;

    /**
     * Controller-related events
     */
    entt::dispatcher JoystickButtonPressedEventDispatcher;
    entt::dispatcher JoystickButtonReleasedEventDispatcher;
    entt::dispatcher JoystickConnectedEventDispatcher;
    entt::dispatcher JoystickDisconnectedEventDispatcher;
    entt::dispatcher JoystickMovedEventDispatcher;

    /**
     * Etc/misc events
     */
    entt::dispatcher SensorChangedEventDispatcher;

    EventHandler() = default;
    ~EventHandler() = default;

    void ProcessEvents(sf::RenderWindow &window);

};
