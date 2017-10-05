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
PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the Play button.
*/
void PlayButtonScript::Start() {
    m_interactive_button = (UIButton *)GetOwner()->GetComponent("UIButton");
}

/**
    @brief Update the text, sound and menu of the Play button.
*/
void PlayButtonScript::ComponentUpdate() {

    // Text component to updates the colors of the Play Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");

    // Sound component to updates the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");

    // Sound component to turn off the sound of the menu
    auto menuSound = (UISound *)SceneManager::GetInstance()->GetCurrentScene()
                                ->GetGameObject("Music")->GetComponent("UISound");

    // Change sound and scene when mouse is clicked
    if (m_interactive_button->IsClicked()) {
        soundButton->Play(0, -1);
        menuSound->Stop();
        AudioController::GetInstance()->PlayAudio("mainSound", -1);
        SceneManager::GetInstance()->SetCurrentScene("Gameplay");
    }

    // Set PlayButton color depending if mouse is over the button or not
    if (m_interactive_button->IsOver()) {
        textButton->SetColor(160, 160, 160, 255);
    } else {
        textButton->SetColor(255, 255, 255, 255);
    }
}
