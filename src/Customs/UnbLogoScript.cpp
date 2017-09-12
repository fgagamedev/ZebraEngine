#include "Customs/UnbLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"
/**
	@file UnbLogoScript.cpp
	@brief Creates the UnB's symbol that shows up during the game opening.
	@copyright MIT License.
*/

/**
    @brief Constructor for the classe UnbLogoScript.
*/
UnbLogoScript::UnbLogoScript(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void UnbLogoScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));

}

/**
    @brief Generates the animations on the screen.
*/
void UnbLogoScript::CreateAnimations(){

    auto unb_LogoSprite = new Image("assets/introunb.png", 0, 0, 5115, 512);
    auto unbAnimation = new Animation(GetOwner(), unb_LogoSprite);
    for (int i = 0; i < 15; i++) {
        unbAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }
    for (int i = 0; i < 15; i++) {
        unbAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    auto unbAnimator = new Animator(GetOwner());
    unbAnimation->SetFramesPerSecond(9);
    unbAnimator->AddAnimation("UNB ANIMATION", unbAnimation);
}

/**
    @brief Handles with changes on the component.
*/
void UnbLogoScript::ComponentUpdate() {
    if (gamecontroller) {
        if (gamecontroller->GetButtonDown(GC_INPUT_X)) {
            SceneManager::GetInstance()->SetCurrentScene("Main");
        }
    }
    if (input->GetKeyPressed(INPUT_RETURN)) {
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }

}

/**
    @brief Updates the component's status every second and stops the animations after
    100 seconds.
*/
void UnbLogoScript::FixedComponentUpdate() {
    time.Update(1);

    animator->PlayAnimation("UNB ANIMATION");

    if (time.GetTime()>=100) {
        animator->StopAllAnimations();
    }
}
