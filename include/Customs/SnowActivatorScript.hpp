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
        activate = 0;
    }
protected:
    void ComponentUpdate() override;

private:
    // Store if the animation has been activated.
    int activate = -1;
    // Store if the animation has runned.
    bool runned = false;
    // Store the time.
    Timer time;
    void CreateAnimations();
    // Object for inputs in the snow activator script.
    InputSystem *input = nullptr;
    // Object for the inputs from the game controller.
    GameController* gameController = nullptr;
    // Animator for the snow script activator.
    Animator *animator = nullptr;
    // Object that store positions in the game.
    Vector *position = nullptr;
    // Attribute not used in the SnowActivatorScript.
    int play = 0;
};
#endif
