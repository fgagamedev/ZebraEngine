#include "Customs/MenuAnimationScript.hpp"

#include <stdio.h>

MenuAnimationScript::MenuAnimationScript(GameObject *owner) : Script(owner) {}

/**
    @brief that function starts the menu animation. Create the animation,
    position and the animator.
*/
void MenuAnimationScript::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
}


/**
    @brief that function creates the menu animation. Create the MenuAnimationScriptAnimator
    as an animator, the mainSprite image, the main animation one and two.
    Set the frame and add the animations to the game.
*/
void MenuAnimationScript::CreateAnimations() {
    // animator
    auto MenuAnimationScriptAnimator = new Animator(GetOwner());

    auto mainSprite = new Image("assets/menu_animation.png", 0, 0, 5456, 256);

    auto mainAnimation = new Animation(GetOwner(), mainSprite);
    for (int i = 0; i < 16; i++) {
        mainAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }


    auto mainAnimation2 = new Animation(GetOwner(), mainSprite);
    for (int i = 0; i <16; i++) {
        mainAnimation2->AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    mainAnimation->SetFramesPerSecond(10);
    mainAnimation2->SetFramesPerSecond(10);

    MenuAnimationScriptAnimator->AddAnimation("mainAnimation", mainAnimation);
    MenuAnimationScriptAnimator->AddAnimation("mainAnimation2", mainAnimation2);
}

/**
    @brief that function updates the components of the menu animation.
*/
void MenuAnimationScript::ComponentUpdate() {
    if (!animator->IsPlaying("mainAnimation") && !initialanimation) {
        initialanimation = true;
        animator->PlayAnimation("mainAnimation");
    }

    if (initialanimation) {
        if (!animator->IsPlaying("mainAnimation"))
        if (!animator->IsPlaying("mainAnimation2") && initialanimation) {
            animator->PlayAnimation("mainAnimation2");
        }
    }
}

/**
    @brief that function fixs the components update of the menu animation. 
*/
void MenuAnimationScript::FixedComponentUpdate() {}
