/**
    @file PlayButtonScript.hpp
    @brief Manages the Play button functions.
    @copyright LGPL. MIT License.
*/

#ifndef __PLAY_BUTTON_SCRIPT__
#define __PLAY_BUTTON_SCRIPT__

#include "Engine/GameObject.hpp"

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"

using namespace std;

class PlayButtonScript : public Script {
public:
    PlayButtonScript(GameObject *owner);
    string GetComponentName() override { return "PlayButtonScript"; };
    void ComponentUpdate() override;
    void Start() override;

private:
    // Sets the Play button as a UIButton
    UIButton *m_uiButton = nullptr;
};

#endif
