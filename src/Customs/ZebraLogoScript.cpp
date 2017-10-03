/**
    @file ZebraLogoScript.cpp
    @brief Manage the animations of the Zebra logo, at the start of the game.
    @copyright MIT License.
*/

#include "Customs/ZebraLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor of the class ZebraLogoScript.
    @param[in] GameObject *owner - Owns the component.
*/
ZebraLogoScript::ZebraLogoScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Starts the animation of the Zebra logo.
*/
void ZebraLogoScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0, 0));

}

/**
    @brief Creates the animations for Zebra logo.
*/
void ZebraLogoScript::CreateAnimations(){
    // Keeps the path, positions x and y, width and height of the Zebra image
    auto zebra_LogoSprite = new Image("assets/introzebra.png", 0, 0, 5115, 512);

    auto zebraAnimation = new Animation(GetOwner(), zebra_LogoSprite);

    // Run through 0 to 14 adding frames in different x positions
    for (int i = 0; i < 15; i++) {
        zebraAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }

    // Run through 0 to 14 adding frames in different x positions
    for (int i = 0; i < 15; i++) {
        zebraAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));
    }
    zebraAnimation->SetFramesPerSecond(9);

    // Insert the ZebraLogo in the map.
    auto zebraAnimator = new Animator(GetOwner());
    zebraAnimator->AddAnimation("ZEBRA ANIMATION", zebraAnimation);

}

/**
    @brief Do nothing.
*/
void ZebraLogoScript::ComponentUpdate() {

}

/**
    @brief Controls the duration of the Zebra logo's animation.
*/
void ZebraLogoScript::FixedComponentUpdate() {

    time.Update(1);

    // Set the time when ZebraLogo will start to be displayed in the screen
    if (time.GetTime() >= 260) {
        animator->PlayAnimation("ZEBRA ANIMATION");
    }

    // Set the time when ZebraLogo will stop to be displayed in the screen
    if (time.GetTime() >= 360) {
        animator->StopAllAnimations();
    }
}
