/**
    @file FirstBossScript.cpp
    @brief Creates and handles with the first boss behavior.
    @copyright MIT License.
*/
#include "Customs/FirstBossScript.hpp"

/**
    @brief Constructor for the class FirstBossScript.
*/
FirstBossScript::FirstBossScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the script of the first boss of the game.
*/
void FirstBossScript::Start() {
    // Create the animations of the first boss
    CreateAnimations();

    // Positions the boss in the game's map.
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    /*
    If map isn't null, set the zoom proportion and create a collider for the
    first boss.
    */
    if (map) {
        GetOwner()->SetZoomProportion(Vector(
                            map->originalWidth/GetOwner()->originalWidth,
                            map->originalHeight/GetOwner()->originalHeight));
        m_firstBossCollider = new RectangleCollider(GetOwner(),
                                                  Vector(0, 0),
                                                  GetOwner()->GetWidth(),
                                                  GetOwner()->GetHeight(), 0);
    }
}

/**
    @brief Creates logic behind the firs boss animations to be shown during the
    game.
*/
void FirstBossScript::CreateAnimations() {
    // Get images from the first boss.
    auto firstBossImage = new Image("assets/boss1.png",0,0,1896, 324);
    auto firstBossJumpImage = new Image("assets/boss1_jump.png",0,0,1180, 406);

    // Create animations for the first boss.
    auto firstBossAnimation = new Animation(GetOwner(),firstBossImage);
    // Add 8 frames, changing the X position of the frame in crescent order.
    const int numberNewFramesBossAnimation = 8;
    for (int i = 0; i < numberNewFramesBossAnimation; i++) {
        firstBossAnimation->AddFrame(new Frame(i * 237,0, 237, 406));
    }

    auto firstBossJumpAnimation = new Animation(GetOwner(),firstBossJumpImage);

    // Possible number of new frames created.
    const int fiveNewFrames = 5;
    const int eightNewFrames = 8;
    // Add 5 frames, changing the X position of the frame in crescent order.
    for (int i = 0; i < fiveNewFrames; i++) {
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));

        // Index of the last frame of the jump animation.
        const int lastFrameJumpAnimation = 4;
        // For the last iteration of the for, add more frames.
        if (i == lastFrameJumpAnimation) {
            /*
            Add 4 frames, changing the X position of the frame in crescent
            order.
            */
            for (int animMulti = 0; i < eightNewFrames; i++) {
                firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236,
                                                           406));
                firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236,
                                                           406));
            }
        }
    }

    // Create a animation for the fall of the first boss.
    auto firstBossFallAnimation = new Animation(GetOwner(),firstBossJumpImage);
    // Add 5 frames, changing the X position of the frame in decrescent order.
    for (int i = fiveNewFrames; i > 0; i--) {
        firstBossFallAnimation->AddFrame(new Frame(i * 236, 0, 236, 406));
        firstBossFallAnimation->AddFrame(new Frame(i * 236, 0, 236, 406));
    }

    // Creates the m_animator for the first boss.
    auto firstBossAnimator = new Animator(GetOwner());
    firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);
    firstBossAnimator->AddAnimation("firstBossJumpAnimation",
                                    firstBossJumpAnimation);
    firstBossAnimator->AddAnimation("firstBossFallAnimation",
                                    firstBossFallAnimation);
}

/**
    @brief Decides what happens to the boss depending on the game's circumstances.
*/
void FirstBossScript::ComponentUpdate() {
    /*
    Play the firstBossAnimation animation if isn't the second attack and the
    second attack doesn't fall.
    */
    if (!m_secondAttack && !m_secondAttackFall) {
        //Idle animation
        m_animator->PlayAnimation("firstBossAnimation");
    }

    /*
    If the INPUT_N key get pressed, start the second attack and play the
    firstBossJumpAnimation animation.
    */
    if (m_input->GetKeyPressed(INPUT_N)) {
        m_secondAttack = true;
        m_animator->PlayAnimation("firstBossJumpAnimation");
    }
}

/**
    @brief Handles with the boss behavior depending on which attack is being shot.
*/
void FirstBossScript::FixedComponentUpdate() {
    // If is the first attack, update the timer of the first attack cooldown.
    if (m_firstAttack) {
        m_timerFirstAttackCooldown.Update(EngineGlobals::fixed_update_interval);
    }

    // If the first attack has gone, update the timer of the first attack gone.
    if (m_goneFirstAttack) {
        m_timerFirstAttackGone.Update(EngineGlobals::fixed_update_interval);
    }

    // If is the second attack, update the timer of the second attack.
    if (m_secondAttack) {
        m_timerSecondAttack.Update(EngineGlobals::fixed_update_interval);
    }

    // If is the second attack fall, update the timer of the second attack fall.
    if (m_secondAttackFall) {
        m_timerSecondAttackFall.Update(EngineGlobals::fixed_update_interval);
    }

    // Update the timer of the cooldown of the attacks.
    m_timerAttackCooldown.Update(EngineGlobals::fixed_update_interval);

    Attack();

    // If shake is true, shake the camera of the game.
    if (m_cameraShake) {
        // CameraShake(intensity, duration in seconds)
        CameraSystem::GetInstance()->CameraShake(8,1,
                                SceneManager::GetInstance()->GetCurrentScene());
        if (!CameraSystem::GetInstance()->IsShaking()) {
            m_cameraShake = false;
        }
    }
}

/**
    @brief Manages the shot's position and its behavior, the time it takes to
    happen, etc.
*/
void FirstBossScript::Attack() {
    // Check if the game object is active to start the attack.
    if (GetOwner()->active) {
        // Cooldown time between all attacks.
        const int maxTimeAttackCooldown = 9000;
        // If the cooldown has end, do a new attack.
        if (m_timerAttackCooldown.GetTime() >= maxTimeAttackCooldown) {
            // Choose a new number
            m_randomNumber = rand() % 2;
            m_timerAttackCooldown.Restart();
            cout << m_randomNumber << endl;
        }

        // Default number for the second attack.
        const int secondAttackNumber = 0;
        /*
        Play the first boss's jump animation if is the second attack and it
        doesn't has fall.
        */
        if (m_randomNumber == secondAttackNumber
                        && m_secondAttackFall == false) {
            m_secondAttack = true;
            m_animator->PlayAnimation("firstBossJumpAnimation");
        }

        // Default number for the first attack.
        const int firstAttackNumber = 1;
        // Check if the current attack is the first.
        if (m_randomNumber == firstAttackNumber) {
            m_firstAttack = true;

            // Max number of first attacks before new actions.
            const int maxFirstAttackCounter = 3;
            // Cooldown time for the first attack.
            const int maxTimeFirstAttackCooldown = 2000;
            /*
            Check if the first attack isn't in the cooldown and hasn't been
            used more than 3 times.
            */
            if (m_timerFirstAttackCooldown.GetTime() >= maxTimeFirstAttackCooldown
                    && m_firstAttackCounter < maxFirstAttackCounter) {
                FirstBossController::GetInstance()->FirstAttackSurge();
                // Restart the timer for the first attack and add to the counter.
                m_timerFirstAttackCooldown.Restart();
                m_firstAttackCounter++;
                // Delay for next sord
            }
            // If is the fourth first attack, set the first attack as gone.
            if (m_firstAttackCounter == maxFirstAttackCounter) {
                // Activate timer to gone tentacle
                m_goneFirstAttack = true;
            }

            // Wait 2 seconds to make attack gone
            if (m_timerFirstAttackGone.GetTime() >= maxTimeFirstAttackCooldown) {
                FirstBossController::GetInstance()->FirstAttackGone();

                // Reset the first attack attributes.
                m_firstAttackCounter = 0;
                m_goneFirstAttack = false;
                m_timerFirstAttackGone.Restart();
                m_timerFirstAttackCooldown.Restart();
                m_randomNumber = defaultRandomNumber;
            }
        }

        // Max time for the second attack.
        const int maxTimeSecondAttack = 500;
        // Check if the second attack time has ended.
        if ((m_timerSecondAttack.GetTime() >= maxTimeSecondAttack)
                    && m_secondAttack) {
            // Check if the boss position is over the lower limit.
            if (GetOwner()->GetPosition()->m_y > -1900) {
                Vector *newPosition = GetOwner()->GetPosition();

                newPosition->m_y = newPosition->m_y - 90;
                GetOwner()->SetPosition(*newPosition);
            } else {
                m_secondAttack = false;
                m_secondAttackFall = true;
                m_timerSecondAttack.Restart();
            }
        }

        // Time before the second attack fall.
        const int timeSecondAttackFall = 2000;
        // Check if it is time to end the fall of the second attack.
        if (m_timerSecondAttackFall.GetTime() >= timeSecondAttackFall
                    && m_secondAttackFall) {
            // Get player Position
            m_player = SceneManager::GetInstance()->GetCurrentScene()->
                        GetGameObject("NakedMan");
            m_playerPosition.m_x = m_player->GetPosition()->m_x - 160;
            m_playerPosition.m_y = m_player->GetPosition()->m_y - 450;
            cout << "flag" << endl;

            std::cout << m_playerPosition.m_x << "  " << m_playerPosition.m_y << std::endl;

            // Set the horizontal position of the boss's fall.
            GetOwner()->m_position->m_x = m_playerPosition.m_x;
            /*
            Check the vertical position of the boss's fall and change it
            depending of the player's position besides play the fall animation.
            */
            if (GetOwner()->m_position->m_y < m_playerPosition.m_y) {
                GetOwner()->m_position->m_y += 90;
                m_cameraShake = true;
                m_animator->PlayAnimation("firstBossFallAnimation");
            // Don't fall and don't shake the camera.
            } else {
                m_secondAttackFall = false;
                m_cameraShake = false;
                m_randomNumber = defaultRandomNumber;
            }
        }
    }
}
