/**
    @file HitScripr.hpp
    @brief Responsible for organizing sound effects script.
    @copyright MIT License.
*/

#ifndef __HIT_SCRIPT__
#define __HIT_SCRIPT__

#include "Components/Animator.hpp"
#include "Components/Script.hpp"

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/Timer.hpp"

#include "Math/Vector.hpp"

#include <string>

class HitScript : public Script {

public:

    HitScript(GameObject *owner);

    std::string GetComponentName() override {
        return "HitScript";
    };

    void FixedComponentUpdate() override;

    void Start() override;

    bool hit = false;

    int hitLevel = 0;

private:

    void CreateAnimations();

    InputSystem *input = nullptr;

    Animator *animator = nullptr;

    Vector *position = nullptr;

    Timer timerRecover;

protected:

    void ComponentUpdate() override;

};

#endif
