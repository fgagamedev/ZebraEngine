/**
    @file UnbLogoScript.cpp
    @brief Creates the UnB's symbol that shows up during the game opening.
    @copyright MIT License.
*/
#include "Customs/RainScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the class RainScript.
*/
RainScript::RainScript(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the RainScript first definitions.
*/
void RainScript::Start() {
    // Create the animations and the animator for the rain script.
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    // Get the input.
    m_input = InputSystem::GetInstance();
    // Set the zoom proportion.
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Builds the rain animations.
*/
void RainScript::CreateAnimations() {
    // Creates the animations for the rain script.
    auto rainImage = new Image("assets/chuva.png",0,0,3410, 256);
    auto rainAnimation= new Animation(GetOwner(),rainImage);
    // Add 10 frames in the rain animation.
    // Number of frames to add in the animation.
    const int numberNewFrames = 10;
    for (int i = 0; i < numberNewFrames; i++) {
        rainAnimation->AddFrame(new Frame(i * 341,0, 341, 256));
    }

    // Creates the animator for the rain script.
    auto weatherAnimator = new Animator(GetOwner());
    weatherAnimator->AddAnimation("rainAnimation", rainAnimation);
}

/**
    @brief Updates the component's status/ changes during the game.
*/
void RainScript::ComponentUpdate() {
    // Check if the animation must be played.
    if (m_play == startPlay) {
        // Play the rain animation.
        m_animator->PlayAnimation("rainAnimation");
    }

    // Check if the INPUT_R key is pressed and m_play is set to 0.
    if (m_input->GetKeyDown(INPUT_R) && m_play == stopPlay) {
        // Play the rain sound and set m_play to 1.
        AudioController::GetInstance()->PlayAudio("rainSound", -1);
        m_play = startPlay;
    // Check if the INPUT_R key is pressed and m_play is set to 1.
    } else if (m_input->GetKeyDown(INPUT_R) && m_play == startPlay) {
        // Set m_play to 0 and stop all animations playing.
        m_play = stopPlay;
        m_animator->StopAllAnimations();
    }
}

/**
    @brief Sets the position of the owner as 0 on x and 0 on y.
*/
void RainScript::FixedComponentUpdate() {
    // Set the positions X and Y of the component.
    // Coordinate for the position.
    const int valuePosition = 0;
    m_position->m_x = valuePosition;
    m_position->m_y = valuePosition;
}
