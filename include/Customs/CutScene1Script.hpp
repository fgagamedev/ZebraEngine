#ifndef __CUT_SCENE1_SCRIPT__
#define __CUT_SCENE1_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class CutScene1Script : public Script {

public:
    CutScene1Script(GameObject *owner);
    std::string GetComponentName() override {
        return "CutScene1Script";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate() {
        active = true;
    }

protected:
    void ComponentUpdate() override;

private:
    bool active=false;
    Timer time;
    void CreateAnimations();
    InputSystem *input = nullptr;
    GameController* gamecontroller = nullptr;
    Animator *animator = nullptr;
    Vector *position = nullptr;
    int play=0;

};
#endif
