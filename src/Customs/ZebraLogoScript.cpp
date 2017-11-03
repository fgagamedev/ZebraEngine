/**
    @file ZebraLogoScript.cpp
    @brief Manage the animations of the Zebra logo, at the start of the game.
    @copyright MIT License.
*/

#include "Customs/ZebraLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

const int width = 341;
const int height = 256;

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
    zebra_position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0, 0));
}

/**
    @brief Creates the animations for Zebra logo.
*/
void ZebraLogoScript::CreateAnimations(){
    // Keeps the path, positions x and y, width and height of the Zebra image
    auto zebraSprite = new Image("assets/introzebra.png", 0, 0,
                                 width * 15, height * 2);

    auto zebraAnimation = new Animation(GetOwner(), zebraSprite);

    // Run through 0 to 14 adding frames in different x positions
    for (int i = 0; i < 15; i++) {
        zebraAnimation->AddFrame(new Frame(i * width, height - height,
                                           width, height));
    }

    // Run through 0 to 14 adding frames in different x positions
    for (int i = 0; i < 15; i++) {
        zebraAnimation->AddFrame(new Frame(i * width, height, width, height));
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
