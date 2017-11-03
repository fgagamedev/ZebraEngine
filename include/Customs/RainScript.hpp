/**
    @file UnbLogoScript.hpp
    @brief Creates the UnB's symbol that shows up during the game opening.
    @copyright MIT License.
*/
#ifndef __RAIN_SCRIPT__
#define __RAIN_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Customs/AudioController.hpp"
#include "Math/Vector.hpp"

#include <string>

class RainScript : public Script {
public:
    RainScript(GameObject *owner);
    std::string GetComponentName() override {
        return "RainScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    // Store if the animation must be played.
    int m_play = stopPlay;

protected:
    void ComponentUpdate() override;

private:
    void CreateAnimations();
    // Object for inputs in the rain script.
    InputSystem *m_input = nullptr;
    // Animator for the rain script.
    Animator *m_animator = nullptr;
    // Object that store positions in the game.
    Vector *m_position = nullptr;

    // Set if the play must start or stop.
    const int startPlay = 1;
    const int stopPlay = 0;
};

#endif
