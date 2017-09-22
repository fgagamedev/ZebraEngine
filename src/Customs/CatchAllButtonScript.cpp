/**
    @file CatchAllButtonScript.cpp
    @brief Manages the Catch All button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/CatchAllButtonScript.hpp"

/**
    @brief Constructor of the class CatchAllButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
CatchAllButtonScript::CatchAllButtonScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the Catch All button.
*/
void CatchAllButtonScript::Start() {
    m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
    m_checkbox = SceneManager::GetInstance()->GetScene("Main")->GetGameObject(
                 "CatchAll_CB");
}

/**
    @brief Updates the Quit button informations.
*/
void CatchAllButtonScript::ComponentUpdate() {
    if (m_uiButton->IsClicked()) {
        MenuController::GetInstance()->SelectGamemode(0x02);
    }
    if (MenuController::GetInstance()->GetGamemode() & 0x02) {
        m_checkbox->active = true;
    } else {
        m_checkbox->active = false;
    }
}
