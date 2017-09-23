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

    // Get the component name and replace it by returning its string name.
    std::string GetComponentName() override {
        return "CutScene1Script";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Activate() {
        active = true;
    }

private:

    // Boolean variable that stores true or false that turns the scene on or off.
    bool m_active = false;

    void CreateAnimations();

    // Pointer to game controls.
    InputSystem *m_input = nullptr;

    // Pointer to game controller.
    GameController* m_gamecontroller = nullptr;

    // Pointer to animator game.
    Animator *m_animator = nullptr;

    // Poiter to position of gamer.
    Vector *m_position = nullptr;
    int play = 0;

protected:
    void ComponentUpdate() override;

};
#endif
