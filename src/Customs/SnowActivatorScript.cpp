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
    // Index of the controller.
    const int gameControllerIndex = 0;
    m_gameController = m_input->GetGameController(gameControllerIndex);

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
    // Number of new frames added to the animation.
    const int numberOfNewFrames = 13;
    // Add 13 new frames to the snow activator animation.
    for (int i = 0; i < numberOfNewFrames; i++) {
        snowActivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    // Create another animation for the snow activator
    auto snowActivatorAnimation2 = new Animation(GetOwner(),
                                                 snowActivatorSprite);
    snowActivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    // Creates a new animator for the snow activator.
    auto snowActivatorAnimator = new Animator(GetOwner());
    // Number of frames to show in each second
    const int numberOfFrames = 9;
    // Setup the animator.
    snowActivatorAnimation->SetFramesPerSecond(numberOfFrames);
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
                    && m_activateAnimation == animationActivated
                    && m_runnedAnimation == false) {
        // Play the animation.
        m_animator->PlayAnimation("SNOW ACTIVATOR ANIMATION");
        m_activateAnimation = animationEnded;
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
        auto script = (LeftCenterLightScript*)SceneManager::GetInstance()->
                            GetCurrentScene()->
                            GetGameObject("CENTRAL LIGHT 2")->
                            GetComponent("LeftCenterLightScript");
        script->Activate();
        // Get the MapScript of the current scene.
        auto map = (MapScript*)SceneManager::GetInstance()->
                            GetCurrentScene()->GetGameObject("Map")->
                            GetComponent("MapScript");
        // Index of the wall changed
        const int indexOfWall = 49;
        // New value in the walls parameters.
        const float defaultWallsMetricsValues = 0;
        // Set the dimensions of the right walls of the map.
        map->rightWalls[indexOfWall].m_x = defaultWallsMetricsValues;
        map->rightWalls[indexOfWall].m_y = defaultWallsMetricsValues;
        map->rightWalls[indexOfWall].m_w = defaultWallsMetricsValues;
        map->rightWalls[indexOfWall].m_h = defaultWallsMetricsValues;

        // Set the dimensions of the original's right walls of the map.
        map->rightWallsOriginal[indexOfWall].m_x = defaultWallsMetricsValues;
        map->rightWallsOriginal[indexOfWall].m_y = defaultWallsMetricsValues;
        map->rightWallsOriginal[indexOfWall].m_w = defaultWallsMetricsValues;
        map->rightWallsOriginal[indexOfWall].m_h = defaultWallsMetricsValues;
    }

}

/**
    @brief Do nothing.
*/
void SnowActivatorScript::FixedComponentUpdate() {}
