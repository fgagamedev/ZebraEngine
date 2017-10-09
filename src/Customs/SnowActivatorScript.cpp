/**
    @file SnowActivatorScript.cpp
    @brief Manages the snow scenario during the game.
    @copyright MIT License.
*/
#include "Customs/SnowActivatorScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/LeftCenterLightScript.hpp"
#include "Customs/MapScript.hpp"

/**
    @brief Constructor for the class SnowActivatorScript.
*/
SnowActivatorScript::SnowActivatorScript(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the SnowActivator first definitions.
*/
void SnowActivatorScript::Start() {
    // Creates the animations of snow.
    CreateAnimations();

    // Get the position and the animator of the snow.
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");

    // Get the inputs.
    m_input = InputSystem::GetInstance();
    m_gameController = m_input->GetGameController(0);

    // Set the default zoom for the snow.
    GetOwner()->SetZoomProportion(Vector(0,0));

    // Get the map.
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Check if the map was retrieved sucessfully.
    if (map) {
        // Set the zoom for the snow.
        GetOwner()->SetZoomProportion(Vector(
                            map->originalWidth / GetOwner()->originalWidth,
                            map->originalHeight / GetOwner()->originalHeight));
    }
}

/**
    @brief Builds the snow animations.
*/
void SnowActivatorScript::CreateAnimations() {
    // Create the animation for the snow activator.
    auto snowActivatorSprite = new Image("assets/snowactivator.png",
                                         0, 0,832, 64);
    auto snowActivatorAnimation = new Animation(GetOwner(),
                                                snowActivatorSprite);
    // Add 13 new frames to the snow activator animation.
    for (int i = 0; i < 13; i++) {
        snowActivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    // Create another animation for the snow activator
    auto snowActivatorAnimation2 = new Animation(GetOwner(),
                                                 snowActivatorSprite);
    snowActivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    // Creates a new animator for the snow activator.
    auto snowActivatorAnimator = new Animator(GetOwner());
    // Setup the animator.
    snowActivatorAnimation->SetFramesPerSecond(9);
    snowActivatorAnimator->AddAnimation("SNOW ACTIVATOR ANIMATION",
                                        snowActivatorAnimation);
    snowActivatorAnimator->AddAnimation("SNOW ACTIVATOR ANIMATION2",
                                        snowActivatorAnimation2);

}

/**
    @brief Updates the component's status/ changes during the game.
*/
void SnowActivatorScript::ComponentUpdate() {
    // Play the SNOW ACTIVATOR ANIMATION if isn't playing and has been activated.
    if (!m_animator->IsPlaying("SNOW ACTIVATOR ANIMATION")
                    && m_activateAnimation == 0 && m_runnedAnimation == false) {
        // Play the animation.
        m_animator->PlayAnimation("SNOW ACTIVATOR ANIMATION");
        m_activateAnimation = 1;
        m_runnedAnimation = true;
    }

    /*
    Play the SNOW ACTIVATOR ANIMATION2 if the SNOW ACTIVATOR ANIMATION has
    ended playing.
    */
    if (m_runnedAnimation
                    && !m_animator->IsPlaying("SNOW ACTIVATOR ANIMATION")) {
        // Play the animation.
        m_animator->PlayAnimation("SNOW ACTIVATOR ANIMATION2");
    }
    // Check if the snow animation has run.
    if (m_runnedAnimation) {
        // Get the LeftCenterLightScript of the current scene.
        auto script = (LeftCenterLightScript*)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("CENTRAL LIGHT 2")->GetComponent("LeftCenterLightScript");
        script->Activate();
        // Get the MapScript of the current scene.
        auto map = (MapScript*)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("Map")->GetComponent("MapScript");
        // Set the dimensions of the right walls of the map.
        map->rightWalls[49].m_x = 0;
        map->rightWalls[49].m_y = 0;
        map->rightWalls[49].m_w = 0;
        map->rightWalls[49].m_h = 0;

        // Set the dimensions of the original's right walls of the map.
        map->rightWallsOriginal[49].m_x = 0;
        map->rightWallsOriginal[49].m_y = 0;
        map->rightWallsOriginal[49].m_w = 0;
        map->rightWallsOriginal[49].m_h = 0;
    }

}

/**
    @brief Do nothing.
*/
void SnowActivatorScript::FixedComponentUpdate() {}
