#ifndef __CENTRAL_LIGHT_SCRIPT2__
#define __CENTRAL_LIGHT_SCRIPT2__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

/**
    @file LeftCenterLightScript.hpp
    @brief This class contains all attributes and methods that manages the central light in the game.
    @copyright LGPL. MIT License.
*/

class LeftCenterLightScript : public Script {

public:
    LeftCenterLightScript(GameObject *owner);
    std::string GetComponentName() override {
        return "LeftCenterLightScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate(){
        active = true;
    }

protected:
    void ComponentUpdate() override;

private:
    void CreateAnimations();
    /*
    the player has to find the central light and pass through it to activate
    it, this variable was created in order to control whether the player has
    passed through it or not
    */
    bool active = false;
    int play = 0;
    Timer time;
    InputSystem *input = nullptr;
    GameController* gamecontroller = nullptr;
    Animator *animator = nullptr;
    Vector *position = nullptr;
};

#endif
