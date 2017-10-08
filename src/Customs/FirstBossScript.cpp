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
    for (int i = 0; i < 8; i++) {
        firstBossAnimation->AddFrame(new Frame(i * 237,0, 237, 406));
    }

    auto firstBossJumpAnimation = new Animation(GetOwner(),firstBossJumpImage);
    // Add 5 frames, changing the X position of the frame in crescent order.
    for (int i = 0; i < 5; i++) {
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));

        // For the last iteration of the for, add more frames.
        if (i == 4) {
            /*
            Add 4 frames, changing the X position of the frame in crescent
            order.
            */
            for (int animMulti = 0; i < 8; i++) {
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
    for (int i = 5; i > 0; i--) {
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
    if (m_shakeCamera) {
        // CameraShake(intensity, duration in seconds)
        CameraSystem::GetInstance()->CameraShake(8,1,
                                SceneManager::GetInstance()->GetCurrentScene());
        if (!CameraSystem::GetInstance()->IsShaking()) {
            m_shakeCamera = false;
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
        // If the cooldown has end, do a new attack.
        if (m_timerAttackCooldown.GetTime() >= 9 * 1000) {
            // Choose a new number
            m_randomNumber = rand() % 2;
            m_timerAttackCooldown.Restart();
            cout << m_randomNumber << endl;
        }

        /*
        Play the first boss's jump animation if is the second attack and it
        doesn't has fall.
        */
        if (m_randomNumber == 0 && m_secondAttackFall == false) {
            m_secondAttack = true;
            m_animator->PlayAnimation("firstBossJumpAnimation");
        }

        // Check if the current attack is the first.
        if (m_randomNumber == 1) {
            m_firstAttack = true;
            /*
            Check if the first attack isn't in the cooldown and hasn't been
            used more than 3 times.
            */
            if (m_timerFirstAttackCooldown.GetTime() >= 2 * 1000
                    && m_firstAttackCounter < 3) {
                FirstBossController::GetInstance()->FirstAttackSurge();
                // Restart the timer for the first attack and add to the counter.
                m_timerFirstAttackCooldown.Restart();
                m_firstAttackCounter++;
                // Delay for next sord
            }
            // If is the fourth first attack, set the first attack as gone.
            if (m_firstAttackCounter == 3) {
                // Activate timer to gone tentacle
                m_goneFirstAttack = true;
            }

            // Wait 2 seconds to make attack gone
            if (m_timerFirstAttackGone.GetTime() >= 2 * 1000) {
                FirstBossController::GetInstance()->FirstAttackGone();

                // Reset the first attack attributes.
                m_firstAttackCounter = 0;
                m_goneFirstAttack = false;
                m_timerFirstAttackGone.Restart();
                m_timerFirstAttackCooldown.Restart();
                m_randomNumber = -1;
            }
        }

        if ((m_timerSecondAttack.GetTime() >= 0.5 * 1000) && m_secondAttack) {
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

        // Check if it is time to end the fall of the second attack.
        if (m_timerSecondAttackFall.GetTime() >= 2 * 1000 && m_secondAttackFall) {
            // Get player Position
            m_player = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
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
                m_shakeCamera = true;
                m_animator->PlayAnimation("firstBossFallAnimation");
            // Don't fall and don't shake the camera.
            } else {
                m_secondAttackFall = false;
                m_shakeCamera = false;
                m_randomNumber = -1;
            }
        }
    }
}
