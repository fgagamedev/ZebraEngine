/**
    @file ControleLogoScript.cpp
    @brief Manage the animations of the control logo, at the start of the game.
    @copyright MIT License.
*/

#include "Customs/ControleLogoScript.hpp"

#include "Globals/EngineGlobals.hpp"

#include <stdio.h>

/**
    @brief Constructor for the ControleLogoScript class.
*/
ControleLogoScript::ControleLogoScript(GameObject *owner) : Script(owner) {}

/**
    @brief Start the animation of the controle logo.
*/
void ControleLogoScript::Start() {
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Create the animations for controle logo.
*/
void ControleLogoScript::CreateAnimations() {
    auto controle_LogoSprite = new Image("assets/introcontrole.png", 0, 0, 5115,
                                         512);
    auto controleAnimation = new Animation(GetOwner(), controle_LogoSprite);
    for (int i = 0; i < 15; i++) {
        controleAnimation -> AddFrame(new Frame(i * 341, 0, 341, 256));
    }
    for (int i = 0; i < 15; i++) {
        controleAnimation -> AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    auto controleAnimator = new Animator(GetOwner());
    controleAnimation -> SetFramesPerSecond(9);
    controleAnimator -> AddAnimation("CONTROLE ANIMATION", controleAnimation);
}

/**
    @brief Do nothing.
*/
void ControleLogoScript::ComponentUpdate() {}

/**
    @brief Control the duration of the controle logo's animation.
*/
void ControleLogoScript::FixedComponentUpdate() {
    time.Update(1);
    if (time.GetTime() >= 390) {
        m_animator->PlayAnimation("CONTROLE ANIMATION");
    }
    if (time.GetTime() >= 490) {
        m_animator->StopAllAnimations();
    }

    if (time.GetTime() >= 530) {
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }
}
