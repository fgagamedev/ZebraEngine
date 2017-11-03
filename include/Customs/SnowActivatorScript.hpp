/**
    @file SnowActivatorScript.hpp
    @brief Manages the snow scenario during the game.
    @copyright MIT License.
*/
#ifndef __SNOW_ACTIVATOR_SCRIPT__
#define __SNOW_ACTIVATOR_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class SnowActivatorScript : public Script {
public:
    SnowActivatorScript(GameObject *owner);
    std::string GetComponentName() override {
        return "SnowActivatorScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate() {
        m_activateAnimation = animationActivated;
    }
protected:
    void ComponentUpdate() override;

private:
    // Store if the animation has been activated.
    int m_activateAnimation = animationNotActivated;
    // Store if the animation has runned.
    bool m_runnedAnimation = false;
    // Store the m_time.
    Timer m_time;
    void CreateAnimations();
    // Object for inputs in the snow activator script.
    InputSystem *m_input = nullptr;
    // Object for the inputs from the game controller.
    GameController* m_gameController = nullptr;
    // Animator for the snow script activator.
    Animator *m_animator = nullptr;
    // Object that store positions in the game.
    Vector *m_position = nullptr;
    // Attribute not used in the SnowActivatorScript.
    int m_play = 0;

    // Animation possible status.
    const int animationNotActivated = -1;
    const int animationActivated = 0;
    const int animationEnded = 1;
};
#endif
