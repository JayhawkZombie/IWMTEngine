//
// Created by Kurt Slagle on 1/4/25.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <string>
#include <vector>
#include <memory>

class GameObject;

class Level {
public:
    std::string name = "<unnamed>";
    entt::sigh<void()> OnDestroySignal;
    entt::sigh<void()> OnInitSignal;
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    Level();
    virtual ~Level();

    virtual void Init();
    virtual void Destroy();
    virtual void Render(sf::RenderTarget &target);
    virtual void Tick(double delta);

    void RenderLevelEditor();
    virtual void RenderEditor();
    bool IsInitialized();

protected:

    void SetIsInitialized(bool isInit);

private:

    bool isInitialized = false;

};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(Level)
RENGINE_REFLECT_CLASS_MEMBER(std::string, name, "name")
RENGINE_REFLECT_CLASS_MEMBER(std::vector<std::shared_ptr<GameObject>>, gameObjects, "gameObjects")
RENGINE_REFLECT_CLASS_END(Level)
