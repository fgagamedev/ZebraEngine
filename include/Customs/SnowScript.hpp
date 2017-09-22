/**
    @file nowScript.cpp
    @brief This class contains all attributes and methods that manages the
    snow in the game.
    @copyright LGPL. MIT License.
*/

#ifndef __SNOW_SCRIPT__
#define __SNOW_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"

#include "Customs/AudioController.hpp"

#include <string>

class SnowScript : public Script {

    public:
        SnowScript(GameObject *owner);
        std::string GetComponentName() override {
            return "SnowScript";
        };
        void FixedComponentUpdate() override;
        void Start() override;

        // State of the script.
        int play = 0;

    protected:
        void ComponentUpdate() override;

    private:
        void CreateAnimations();

        // Instantiating input system of the keyboard.
        InputSystem *input = nullptr;

        // Instantiating animations.
        Animator *animator = nullptr;

        // Instantiating vector.
        Vector *position = nullptr;
};

#endif
