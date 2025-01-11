//
// Created by Kurt Slagle on 12/30/24.
//

#include "GameObject.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

void GameObject::Tick(double delta) {
}

void GameObject::Init() {
}

void GameObject::Render(sf::RenderWindow &window) {
}

void GameObject::SetPosition(const sf::Vector2f &newPos) {
    EventDispatcher.enqueue<GameObject::PositionChangedEvent>({position, newPos});
    position = newPos;
}

const sf::Vector2f & GameObject::GetPosition() const {
    return position;
}

void GameObject::SetSize(const sf::Vector2f &newSize) {
    EventDispatcher.enqueue<GameObject::SizeChangedEvent>({size, newSize});
    size = newSize;
}

const sf::Vector2f & GameObject::GetSize() const {
    return size;
}

void GameObject::SetAwake(bool shouldBeAwake) {
    EventDispatcher.enqueue<GameObject::AwakeChangedEvent>({awake, shouldBeAwake});
    awake = shouldBeAwake;
}

bool GameObject::IsAwake() const {
    return awake;
}

void GameObject::PostTick() {
    EventDispatcher.update<GameObject::PositionChangedEvent>();
    EventDispatcher.update<GameObject::SizeChangedEvent>();
    EventDispatcher.update<GameObject::AwakeChangedEvent>();
}
