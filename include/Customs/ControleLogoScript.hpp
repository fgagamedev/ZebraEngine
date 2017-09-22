/**
    @file ControleLogoScript.hpp
    @brief Manage the animations of the control logo, at the start of the game.
    @copyright MIT License.
*/
#ifndef __CONTROLE_LOGO_SCRIPT__
#define __CONTROLE_LOGO_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>


class ControleLogoScript : public Script {

public:
    ControleLogoScript(GameObject *owner);
    std::string GetComponentName() override {
        return "ControleLogoScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

private:

    // Variable of the type Timer responsible for storing the duration time.
    Timer time;
    void CreateAnimations();

    // Pointer to game controls
    InputSystem *m_input = nullptr;

    // Pointer to animator game.
    Animator *m_animator = nullptr;

    // Poiter to position of gamer.
    Vector *m_position = nullptr;


protected:
    void ComponentUpdate() override;

};

#endif
