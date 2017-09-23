#include "Customs/QuitButtonScript.hpp"

/**
    @file QuitButtonScript.hpp
    @brief Manages the Quit button functions.
    @copyright LGPL. MIT License.
*/

/**
    @brief Constructor of the class QuitButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the Quit button.
*/
void QuitButtonScript::Start() {
    m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

/**
    @brief Updates the text and sound of the Quit button.
*/
void QuitButtonScript::ComponentUpdate() {
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");

    if (m_uiButton->IsClicked()) {
        soundButton->Play(0, -1);
        SDLSystem::GetInstance()->SetRunning(false);
    }

    if (m_uiButton->IsOver()) {
        textButton->SetColor(160,160,160, 255);
    } else {
        textButton->SetColor(255,255,255, 255);
    }
}
