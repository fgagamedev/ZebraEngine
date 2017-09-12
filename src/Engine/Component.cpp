#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Log/log.hpp"
/**
	@file Component.cpp
	@copyright MIT License.
*/

Component::Component(GameObject *owner, ComponentType type) {
    if (!owner) {
        ERROR("Invalid null owner");
    }
    m_owner = owner;
    m_type = type;
    m_owner->AddComponent(this);
}

Component::~Component() {
    m_owner = nullptr;
}

void Component::Update() {
    ComponentUpdate();
}
