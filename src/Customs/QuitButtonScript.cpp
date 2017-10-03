/**
    @file QuitButtonScript.cpp
    @brief Manages the Quit button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/QuitButtonScript.hpp"

/**
    @brief Constructor of the class QuitButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {
    
}

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
    // Text component to set the colors of the Quit Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");

    // Sound component to play the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");

    // Change sound and running status when mouse is clicked
    if (m_uiButton->IsClicked()) {
        soundButton->Play(0, -1);
        SDLSystem::GetInstance()->SetRunning(false);
    }

    // Set QuitButton color depending if mouse is over the button or not
    if (m_uiButton->IsOver()) {
        textButton->SetColor(160,160,160, 255);
    } else {
        textButton->SetColor(255,255,255, 255);
    }
}
