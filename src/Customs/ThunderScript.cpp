#include "Customs/ThunderScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @file ThunderScript.cpp
    @brief Manage the thunders animations of the game.
*/

/**
    @brief Constructor for the ThunderScript class.
    @param[in] owner
*/
ThunderScript::ThunderScript(GameObject *owner) : Script(owner) {}

/**
    @brief Start the animation for thunder in game.
*/
void ThunderScript::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Create animations of thunders with different colors.
*/
void ThunderScript::CreateAnimations() {
    auto thunderImage = new Image("assets/Sprites/dashes.png", 0, 0, 2952, 815);

    auto thunderBlueAnimation = new Animation(GetOwner(), thunderImage);
    for (int i = 0; i < 6; i++) {
        thunderBlueAnimation->AddFrame(new Frame(i * 100, 135, 100, 267));
    }

    auto thunderYellowAnimation = new Animation(GetOwner(),thunderImage);
    for (int i = 0; i < 5; i++) {
        thunderYellowAnimation->AddFrame(new Frame(555 + (i * 59), 135, 59,
                                                   267));
    }

    // animator
    auto thunderAnimator = new Animator(GetOwner());

    thunderAnimator->AddAnimation("thunderBlueAnimation", thunderBlueAnimation);
    thunderAnimator->AddAnimation("thunderYellowAnimation",
    thunderYellowAnimation);
}

/**
    @brief Change the thunder animation based on the pressed button.
*/
void ThunderScript::ComponentUpdate() {
    if (input->GetKeyDown(INPUT_1)) {
        animator->PlayAnimation("thunderBlueAnimation");
    }

    if (input->GetKeyDown(INPUT_2)) {
        animator->PlayAnimation("thunderYellowAnimation");
    } else {
        //animator->StopAllAnimations();
    }

}

/**
    @brief Do nothing.
*/
void ThunderScript::FixedComponentUpdate() {
    //position->m_x=0;
    //position->m_y=0;
}
