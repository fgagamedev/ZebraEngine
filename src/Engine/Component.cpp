/**
    @file Component.cpp
    @brief Manage the components of the game.
	@copyright MIT License.
*/

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Log/log.hpp"

/**
    @brief Constructor of Component's class.
*/
Component::Component(GameObject *owner, ComponentType type) {
    // Test if owner exists and show a error if doesn't exists.
    if (!owner) {
        ERROR("Invalid null owner");
    }
    // Instance the owner and type objects
    m_owner = owner;
    m_type = type;
    m_owner->AddComponent(this);
}

/**
    @brief Destructor of Component's class.
*/
Component::~Component() {
    m_owner = nullptr;
}

/**
    @brief Updates the component.
*/
void Component::Update() {
    ComponentUpdate();
}
