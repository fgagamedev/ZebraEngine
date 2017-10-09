/**
    @file LightScript.hpp
    @brief Class that represents the script of light of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __LIGHT_SCRIPT__
#define __LIGHT_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>


class LightScript : public Script {

public:
    LightScript(GameObject *owner);
    std::string GetComponentName() override {
        return "RainScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

private:
    void CreateAnimations();

    // Instantiating input system of the keyboard.
    InputSystem *input = nullptr;

    // Instantiating animations.
    Animator *animator = nullptr;

    // Instantiating lightscript position, type vector.
    Vector *position = nullptr;

    // Instantiating player, type gameobject, that has all the fundamental game functionalities.
    GameObject *player = nullptr;

    //State of the script.
    int play = 1;

protected:
    void ComponentUpdate() override;

};

#endif
