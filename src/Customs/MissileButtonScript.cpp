/**
    @file MissileButtonScript.hpp
    @brief This class contains all attributes and methods that manages the
    missile button in the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/MissileButtonScript.hpp"

/**
    @brief Initializes MissileButtonScript instance.
    @param[in] GameObject *owner - owns the component.
*/
MissileButtonScript::MissileButtonScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the missile button script, instantiate button and checkbox.
*/
void MissileButtonScript::Start() {
    m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
    m_checkbox = SceneManager::GetInstance()->GetScene("Main")->GetGameObject("Missile_CB");
}

/**
    @brief Updates the button and checkbox components.
*/
void MissileButtonScript::ComponentUpdate() {
    if (m_uiButton->IsClicked()) {
        MenuController::GetInstance()->SelectGamemode(0x01);
    }
    if (MenuController::GetInstance()->GetGamemode() & 0x01) {
        m_checkbox->active = true;
    }
    else {
        m_checkbox->active = false;
    }
}
