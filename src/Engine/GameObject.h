//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

#include <entt/entity/mixin.hpp>
#include <entt/fwd.hpp>
#include <entt/entt.hpp>
#include <entt/signal/sigh.hpp>
#include <SFML/Graphics.hpp>

class GameObject {
public:
    sf::Vector2f position;
    sf::Vector2f size;
    bool awake;

    struct PositionChangedEvent {
        sf::Vector2f oldPosition;
        sf::Vector2f newPosition;
    };

    struct SizeChangedEvent {
        sf::Vector2f oldSize;
        sf::Vector2f newSize;
    };

    struct AwakeChangedEvent {
        bool oldAwake;
        bool newAwake;
    };

    entt::dispatcher EventDispatcher;

    GameObject();
    virtual ~GameObject();

    virtual void Tick(double delta);
    virtual void Init();
    virtual void Render(sf::RenderTarget &target);

    void SetPosition(const sf::Vector2f &newPos);
    const sf::Vector2f &GetPosition() const;
    void SetSize(const sf::Vector2f &newSize);
    const sf::Vector2f &GetSize() const;
    void SetAwake(bool shouldBeAwake);
    bool IsAwake() const;

    void PostTick();
};


#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(GameObject)
RENGINE_REFLECT_CLASS_MEMBER(sf::Vector2, position, "position")
RENGINE_REFLECT_CLASS_MEMBER(sf::Vector2, size, "size")
RENGINE_REFLECT_CLASS_MEMBER(bool, awake, "awake")
RENGINE_REFLECT_CLASS_END(GameObject)
