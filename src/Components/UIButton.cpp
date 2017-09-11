#include "Engine/GameObject.hpp"
#include "Engine/SDLSystem.hpp"

#include "Components/UIButton.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Globals/InputGlobals.hpp"
#include "Log/log.hpp"

/**
    @file UIButton.cpp
    @brief Methods that manages all game's buttons as 'quit' and 'start'.
    @copyright LGPL. MIT License.
*/

UIButton::UIButton(GameObject *owner) : Component(owner, C_DRAW) {}

/**
    @brief Creates a button.
*/
void UIButton::Start() {
    // Case exists
    m_position = GetOwner()->GetPosition();
}

/**
    @brief Checking if mouse is over button and clicked.
    @return Boolean.
*/
bool UIButton::IsClicked() {    
    if (IsOver() && InputSystem::GetInstance()->GetMouseButtonDown(M_INPUT_LEFT))
        return true;
    return false;
  }

/**
    @brief Gets button and mouse positions, and check if mouse is still there.
    @return Boolean.
*/
bool UIButton::IsOver() {

    // Getting button and mouse position
    m_position = GetOwner()->GetPosition();
    int rendererWidth = GetOwner()->GetWidth();
    int rendererHeight = GetOwner()->GetHeight();
    std::pair<int, int> mousePos = InputSystem::GetInstance()->GetMousePosition();

    // Checking if mouse is over
    if (mousePos.first > m_position->m_x &&
        mousePos.first < m_position->m_x + rendererWidth &&
        mousePos.second > m_position->m_y &&
        mousePos.second < m_position->m_y + rendererHeight)
            return true;
    return false;
}
