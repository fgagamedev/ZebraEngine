/**
    @file CatchAllButtonScript.cpp
    @brief Manages the Catch All button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/CatchAllButtonScript.hpp"

const int gameMode = 0x02;

/**
    @brief Constructor of the class CatchAllButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
CatchAllButtonScript::CatchAllButtonScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the Catch All button.
*/
void CatchAllButtonScript::Start() {
    m_interactive_button = (UIButton *)GetOwner()->GetComponent("UIButton");
    m_checkbox = SceneManager::GetInstance()->GetScene("Main")->GetGameObject(
                 "CatchAll_CB");
}

/**
    @brief Update the Quit button informations.
*/
void CatchAllButtonScript::ComponentUpdate() {
    // Select game mode when mouse is clicked
    if (m_interactive_button->IsClicked()) {
        MenuController::GetInstance()->SelectGamemode(gameMode);
    }

    // Change checkbox value comparing the selected game mode
    if (MenuController::GetInstance()->GetGamemode() & gameMode) {
        m_checkbox->active = true;
    } else {
        m_checkbox->active = false;
    }
}
