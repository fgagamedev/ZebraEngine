/**
@file UnbLogoScript.hpp
@brief Creates the UnB's symbol that shows up during the game opening.
@copyright MIT License.
*/
#ifndef __UNB_LOGO_SCRIPT__
#define __UNB_LOGO_SCRIPT__


#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

class UnbLogoScript : public Script {

public:
    UnbLogoScript(GameObject *owner);
    std::string GetComponentName() override { return "UnbLogoScript"; };
    void FixedComponentUpdate() override;
    void Start() override;

protected:
    void ComponentUpdate() override;

private:
    Timer time;
    void CreateAnimations();
    InputSystem *input = nullptr;
    GameController* gamecontroller = nullptr;
    Animator *animator = nullptr;
    Vector *position = nullptr;
    int play=0;

};
#endif
