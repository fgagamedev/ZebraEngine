#include "Customs/CreditsScript.hpp"

#include "Globals/EngineGlobals.hpp"

/**
    @file CreditsScript.cpp
    @brief Manages the credits script of the game.
    @copyright LGPL. MIT License.
*/

/**
    @brief Constructor of the class CreditsScript.
    @param[in] GameObject *owner - Owns the component.
*/
CreditsScript::CreditsScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the credit position.
*/
void CreditsScript::Start() {
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Do nothing.
*/
void CreditsScript::ComponentUpdate() {}

/**
    @brief Sets the credits x and y positions to zero.
*/
void CreditsScript::FixedComponentUpdate() {
    position->m_x = 0;
    position->m_y = 0;
}
