/**
    @file FirstBossScript.cpp
    @brief Creates and handles with the first boss behavior.
    @copyright MIT License.
*/
#ifndef __FIRST_BOSS_SCRIPT__
#define __FIRST_BOSS_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GraphicsSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Script.hpp"
#include "Components/RectangleCollider.hpp"
#include "Components/Animator.hpp"
#include "Customs/FirstBossController.hpp"
#include "Math/Vector.hpp"

#include <string>

class FirstBossScript : public Script {

public:
    FirstBossScript(GameObject *owner);
    std::string GetComponentName() override {
        return "FirstBossScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;
    void Attack();

protected:
    void ComponentUpdate() override;

private:
    void CreateAnimations();

    // Collider for the first boss.
    RectangleCollider *m_firstBossCollider = nullptr;
    // Object for inputs in the first boss script.
    InputSystem *m_input = nullptr;
    // Animator for the first boss.
    Animator *m_animator = nullptr;
    // Object that store positions in the game.
    Vector *m_position = nullptr;
    // Object of the player of the game.
    GameObject *m_player = nullptr;
    // Object for the positions of the player.
    Vector m_playerPosition = Vector(0,0);

    // Timer for the first attack cooldown.
    Timer m_timerFirstAttackCooldown;
    // Timer for when the first attack has gone.
    Timer m_timerFirstAttackGone;
    // Timer for a attack cooldown.
    Timer m_timerAttackCooldown;
    // Timer for the second attack cooldown.
    Timer m_timerSecondAttack;
    // Timer for the second attack fall.
    Timer m_timerSecondAttackFall;

    // Stores if is the first attack of the first boss.
    bool m_firstAttack = false;
    // Stores if the first attack of the first boss has gone.
    bool m_goneFirstAttack = false;
    // Stores if is the second attack of the first boss.
    bool m_secondAttack = false;
    // Stores if is the jump in the second attack of the first boss.
    bool m_secondAttackJump = false;
    // Stores if is the second attack of the first boss has fallen.
    bool m_secondAttackFall = false;

    // Stores if the camera is shaking.
    bool m_cameraShake = false;

    // Stores the number of first attacks.
    int m_firstAttackCounter = 0;
    // Stores a random integer number.
    int m_randomNumber = -1;
};
#endif
