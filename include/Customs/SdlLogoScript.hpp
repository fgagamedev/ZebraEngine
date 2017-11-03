/**
    @file SdlLogoScript.hpp
    @brief Responsible for creating the Simple DirectMedia Layer 
           script at the beginning of the game.
    @copyright MIT License.
*/

#ifndef __SDL_LOGO_SCRIPT__
#define __SDL_LOGO_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"

#include "Math/Vector.hpp"

#include <string>

class SdlLogoScript : public Script {

public:

    SdlLogoScript(GameObject *owner);

    std::string GetComponentName() override {
        return "SdlLogoScript";
    };

    void FixedComponentUpdate() override;

    void Start() override;

private:

    Timer time;

    void CreateAnimations();

    InputSystem *input = nullptr;

    Animator *animator = nullptr;

    Vector *position = nullptr;

    int play = 0;

protected:

    void ComponentUpdate() override;
};

#endif
