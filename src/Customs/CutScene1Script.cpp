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
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    m_gamecontroller = m_input -> GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,
                               map->originalHeight/GetOwner()->originalHeight));
    }
}

/**
    @brief Create the animations of the cut scene 1.
*/
void CutScene1Script::CreateAnimations() {
    auto centrallightSprite = new Image("assets/cut1.png", 0, 0,1705, 255);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 341, 255));

    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);
}

/**
    @brief Update the animation of the cut scene 1.
*/
void CutScene1Script::ComponentUpdate() {
    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }

    if(m_animator->IsPlaying("CENTRAL LIGHT ANIMATION")) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

/**
    @brief Do nothing.
*/
void CutScene1Script::FixedComponentUpdate() {}
