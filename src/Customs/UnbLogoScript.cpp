/**
	@file UnbLogoScript.cpp
	@brief Creates the UnB's symbol that shows up during the game opening.
	@copyright MIT License.
*/
#include "Customs/UnbLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the classe UnbLogoScript.
*/
UnbLogoScript::UnbLogoScript(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void UnbLogoScript::Start() {
    // Creates the logo animations.
    CreateAnimations();
    // Get the position and the animator of the logo
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    // Get the inputs.
    m_input = InputSystem::GetInstance();
    // Index of the controller.
    const int gameControllerIndex = 0;
    m_gameController = m_input->GetGameController(gameControllerIndex);
    // Set the zoom of the logo.
    GetOwner()->SetZoomProportion(Vector(0,0));

}

/**
    @brief Generates the animations on the screen.
*/
void UnbLogoScript::CreateAnimations() {
    // Set the animation of the logo.
    auto unb_LogoSprite = new Image("assets/introunb.png", 0, 0, 5115, 512);
    auto unbAnimation = new Animation(GetOwner(), unb_LogoSprite);

    // Number of frames to add in the animation.
    const int numberNewFrames = 15;
    // Add 15 frames to the animation.
    for (int i = 0; i < numberNewFrames; i++) {
        // Change the horizontal position of the frames in the animation.
        unbAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
    }

    // Add 15 frames to the animation.
    for (int i = 0; i < numberNewFrames; i++) {
        // Change the horizontal position of the frames in the animation.
        unbAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));
    }

    // Set the animator of the logo.
    auto unbAnimator = new Animator(GetOwner());
    // Number of frames to add per second.
    const int numberFramesPerSecond = 9;
    unbAnimation->SetFramesPerSecond(numberFramesPerSecond);
    unbAnimator->AddAnimation("UNB ANIMATION", unbAnimation);
}

/**
    @brief Handles with changes on the component.
*/
void UnbLogoScript::ComponentUpdate() {
    // Check if the player is using a game controller.
    if (m_gameController) {
        // Check if the button GC_INPUT_X of the controller has been pressed.
        if (m_gameController->GetButtonDown(GC_INPUT_X)) {
            // Change the scene during the logo presentation.
            SceneManager::GetInstance()->SetCurrentScene("Main");
        }
    }

    // Check if the key INPUT_RETURN of the keyboard has been pressed.
    if (m_input->GetKeyPressed(INPUT_RETURN)) {
        // Change the scene during the logo presentation.
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }

}

/**
    @brief Updates the component's status every second and stops the animations
    after 100 seconds.
*/
void UnbLogoScript::FixedComponentUpdate() {
    // Time to be added to the timer.
    const float addedTime = 1;
    m_time.Update(addedTime);

    m_animator->PlayAnimation("UNB ANIMATION");

    // Time before stop all animations.
    const float timeLimit = 100;
    // Stop all the animations if the time is bigger than 100 miliseconds.
    if (m_time.GetTime() >= timeLimit) {
        m_animator->StopAllAnimations();
    }
}
