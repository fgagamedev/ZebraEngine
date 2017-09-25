/**
    @file ForestActivator3.hpp
    @brief Class that defines methods and attributes for activating the forest script.
    @copyright LGPL. MIT License.
*/
#ifndef __FOREST_ACTIVATOR_SCRIPT3__
#define __FOREST_ACTIVATOR_SCRIPT3__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>


class ForestActivatorScript3 : public Script {

    public:
        ForestActivatorScript3(GameObject *owner);
        std::string GetComponentName() override {
            return "ForestActivatorScript3";
        };
        void FixedComponentUpdate() override;
        void Start() override;

        // Represents if this is script is activeted or not.
        void Activate(){activate=0;}
    protected:
        void ComponentUpdate() override;
    private:
        // Represents if this is script is activeted or not.
        int activate = -1;

        // Activation of script.
        bool runned = false;

        // Instantiating time system.
        Timer time;

        void CreateAnimations();

        // Instantiating input system of the keyboard.
        InputSystem *input = nullptr;

        // Instantiating joystick.
        GameController* gamecontroller = nullptr;

        // Instantiating animations.
        Animator *animator = nullptr;

        // Instantiating vector.
        Vector *position = nullptr;

        // State of the script.
        int play = 0;

};
#endif
