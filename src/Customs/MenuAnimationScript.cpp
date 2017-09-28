#include "Customs/MenuAnimationScript.hpp"

#include <stdio.h>

// Constructor
MenuAnimationScript::MenuAnimationScript(GameObject *owner) : Script(owner) {

}

/**
    @brief that function starts the menu animation. Create the animation,
    position and the animator.
*/
void MenuAnimationScript::Start() {
    // Create animations.
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
}


/**
    @brief that function creates the animation of the menu animstion. Create the MenuAnimationScriptAnimator
    as an animator, the mainSprite image, the main animation one and two.
    Set the frame and add the animations to the game.
*/
void MenuAnimationScript::CreateAnimations() {
    // Instantiating the menu script animator.
    auto MenuAnimationScriptAnimator = new Animator(GetOwner());

    // Instantiating the menu image and its position.
    auto mainSprite = new Image("assets/menu_animation.png", 0, 0, 5456, 256);

    /*
        Instantiating the main animation and its position.
        A for loop defines the frames in the main animation and in the second main animation.
    */
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
    // Check the current state of the initial animation and animator, if false, plays it.
    if (!animator->IsPlaying("mainAnimation") && !initialanimation) {
        initialanimation = true;
        animator->PlayAnimation("mainAnimation");
    }

    // Check the current state of the initial animation, if true, checks the animator state. If false, plays the animator.
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
void MenuAnimationScript::FixedComponentUpdate() {

}
