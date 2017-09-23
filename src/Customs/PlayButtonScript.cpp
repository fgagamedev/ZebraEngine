/**
    @file PlayButtonScript.cpp
    @brief Manages the Play button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/PlayButtonScript.hpp"
#include "Customs/AudioController.hpp"

/**
    @brief Constructor of the class PlayButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the Play button.
*/
void PlayButtonScript::Start() {
    m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

/**
    @brief Updates the text, sound and menu of the Play button.
*/
void PlayButtonScript::ComponentUpdate() {

    // Text component to updates the colors of the Play Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");

    // Sound component to updates the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");

    // Sound component to turn off the sound of the menu
    auto menuSound = (UISound *)SceneManager::GetInstance()->GetCurrentScene()
                                ->GetGameObject("Music")->GetComponent("UISound");
    if (m_uiButton->IsClicked()) {
        soundButton->Play(0, -1);
        menuSound->Stop();
        AudioController::GetInstance()->PlayAudio("mainSound", -1);
        SceneManager::GetInstance()->SetCurrentScene("Gameplay");
    }

    if (m_uiButton->IsOver()) {
        textButton->SetColor(160,160,160, 255);
    } else {
        textButton->SetColor(255,255,255, 255);
    }
}
