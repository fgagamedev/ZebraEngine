#include "Customs/RainScript.hpp"
#include "Globals/EngineGlobals.hpp"
/**
	@file UnbLogoScript.cpp
	@brief Creates the UnB's symbol that shows up during the game opening.
	@copyright MIT License.
*/

/**
    @brief Constructor for the class RainScript.
*/
RainScript::RainScript(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the RainScript first definitions.
*/
void RainScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));

}

/**
    @brief Builds the rain animations.
*/
void RainScript::CreateAnimations(){

    auto rainImage = new Image("assets/chuva.png",0,0,3410, 256);

    auto rainAnimation= new Animation(GetOwner(),rainImage );
    for (int i = 0; i < 10; i++) {
        rainAnimation->AddFrame(new Frame(i * 341,0, 341, 256));
    }

    // animator
    auto weatherAnimator = new Animator(GetOwner());
    weatherAnimator->AddAnimation("rainAnimation", rainAnimation);

}

/**
    @brief Updates the component's status/ changes during the game.
*/
void RainScript::ComponentUpdate() {

    if (play == 1) {
        animator->PlayAnimation("rainAnimation");
    }


    if (input->GetKeyDown(INPUT_R) && play == 0) {
        AudioController::GetInstance()->PlayAudio("rainSound", -1);
        play = 1;
    } else if (input->GetKeyDown(INPUT_R) && play == 1) {
        play = 0;
        animator->StopAllAnimations();
    }

}

/**
    @brief Sets the position of the owner as 0 on x and 0 on y.
*/
void RainScript::FixedComponentUpdate() {
    position->m_x=0;
    position->m_y=0;
}
