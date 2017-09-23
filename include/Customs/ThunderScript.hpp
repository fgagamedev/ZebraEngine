/**
    @file ThunderScript.hpp
    @brief Manage the thunders animations of the game.
*/
#ifndef __THUNDER_SCRIPT__
#define __THUNDER_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

class ThunderScript : public Script {
public:
    ThunderScript(GameObject *owner);

    // Get the component name and replace it by returning its string name.
    std::string GetComponentName() override {
        return "ThunderScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

private:
    void CreateAnimations();

    // Pointer to game controls
    InputSystem *m_input = nullptr;

    // Pointer to animator game.
    Animator *m_animator = nullptr;

    // Poiter to position of gamer.
    Vector *m_position = nullptr;

    int play = 0;

protected:
    void ComponentUpdate() override;

};
#endif
