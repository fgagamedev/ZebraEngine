#include "Customs/CutScene1Script.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the ThunderScript class.
    @param[in] owner
*/
CutScene1Script::CutScene1Script(GameObject *owner) : Script(owner) {}

/**
    @brief Start the animation for the cut scene 1.
*/
void CutScene1Script::Start() {
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    m_gamecontroller = m_input -> GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Checks for the map, and sets its properties.
    if(map) {
        GetOwner()->SetZoomProportion(Vector(map -> originalWidth / GetOwner()
                                             ->originalWidth, map
                                             -> originalHeight / GetOwner()
                                             -> originalHeight));
    }
}

/**
    @brief Create the animations of the cut scene 1.
*/
void CutScene1Script::CreateAnimations() {

    // Image light sprite.
    auto centrallightSprite = new Image("assets/cut1.png", 0, 0, 1705, 255);

    // Animation light.
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 341, 255));

    // Animation.
    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                       centrallightAnimation);
}

/**
    @brief Update the animation of the cut scene 1.
*/
void CutScene1Script::ComponentUpdate() {
    // Compares the animator state.
    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }

    // Checks the animator state.
    if(m_animator->IsPlaying("CENTRAL LIGHT ANIMATION")) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

/**
    @brief Do nothing.
*/
void CutScene1Script::FixedComponentUpdate() {}
