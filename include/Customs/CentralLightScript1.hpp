/**
	@file CentralLightScript1.hpp
	@brief Responsible for the light animation during the menu screen.
	@copyright MIT License.
*/
#ifndef __CENTRAL_LIGHT_SCRIPT1__
#define __CENTRAL_LIGHT_SCRIPT1__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"

#include "Math/Vector.hpp"
#include "Components/Script.hpp"
#include "Components/Animator.hpp"

#include <string>

class CentralLightScript1 : public Script {

public:
    CentralLightScript1(GameObject *owner);
    std::string GetComponentName() override {
        return "CentralLightScript1";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate() {
        active = true;
    }

protected:
    void ComponentUpdate() override;

private:
    // Store if the script is active.
    bool active = false;
    // Store the time.
    Timer time;
    void CreateAnimations();
    // Object for inputs in the central light script 1.
    InputSystem *input = nullptr;
    // Object for the inputs from the game controller.
    GameController* gamecontroller = nullptr;
    // Animator for the central light script 1.
    Animator *animator = nullptr;
    // Object that store positions in the game.
    Vector *position = nullptr;
    // Not used attribute.
    int play = 0;
};
#endif
