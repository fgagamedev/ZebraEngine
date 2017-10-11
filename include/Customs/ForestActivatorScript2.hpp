/**
    @file ForestActivatorScript2.hpp
    @brief Class that represents the scrip activion of the Forest two.
    @copyright LGPL. MIT License.
*/

#ifndef __FOREST_ACTIVATOR_SCRIPT2__
#define __FOREST_ACTIVATOR_SCRIPT2__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class ForestActivatorScript2 : public Script {

public:
    ForestActivatorScript2(GameObject *owner);
    std::string GetComponentName() override {
        return "ForestActivatorScript2";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate() {
        activate = 0;
    }

private:
    void CreateAnimations();

    //Activation of script.
    int activate = -1;
    bool runned = false;

    // Instantiating time system.
    Timer time;

    // Instantiating input system of the keyboard.
    InputSystem *input = nullptr;

    // Instantiating joystick.
    GameController* gamecontroller = nullptr;

    // Instantiating animations.
    Animator *animator = nullptr;

    // Instantiating vector.
    Vector *position = nullptr;

    //State of the script.
    int play = 0;

protected:
    void ComponentUpdate() override;

};
#endif
