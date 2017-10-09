/**
    @file GameOverScript.hpp
    @brief Class that represents the scrip of the game over.
    @copyright LGPL. MIT License.
*/

#ifndef __GAME_OVER_SCRIPT__
#define __GAME_OVER_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Customs/AudioController.hpp"

#include <string>


class GameOverScript : public Script {

public:
    GameOverScript(GameObject *owner);
    std::string GetComponentName() override {
        return "SnowScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

private:
    void CreateAnimations();

    // Instantiating input system of the keyboard.
    InputSystem *input = nullptr;

    // Instantiating animations.
    Animator *animator = nullptr;

    // Instantiating object position, type vector.
    Vector *position = nullptr;

    //State of the script.
    int play = 0;

protected:
    void ComponentUpdate() override;
};

#endif
