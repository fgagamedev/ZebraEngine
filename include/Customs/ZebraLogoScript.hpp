/**
    @file ZebraLogoScript.hpp
    @brief Manage the animations of the Zebra logo, at the start of the game.
    @copyright MIT License.
*/

#ifndef __ZEBRA_LOGO_SCRIPT__
#define __ZEBRA_LOGO_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class ZebraLogoScript : public Script {

public:
    ZebraLogoScript(GameObject *owner);

    // Replace the component name and return it.
    std::string GetComponentName() override {
        return "ZebraLogoScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

protected:
  void ComponentUpdate() override;

private:
    void CreateAnimations();

    Timer time;

    // Input instance of the ZebraLogo to get the buttons actions in the game
    InputSystem *input = nullptr;

    // Animator instance to handle with the animations in the map
    Animator *animator = nullptr;

    // Position vector of the ZebraLogo
    Vector *position = nullptr;

    int play = 0;
};

#endif
