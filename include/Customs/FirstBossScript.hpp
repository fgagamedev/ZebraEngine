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
    RectangleCollider *firstBossCollider = nullptr;
    // Object for inputs in the first boss script.
    InputSystem *input = nullptr;
    // Animator for the first boss.
    Animator *animator = nullptr;
    // Object that store positions in the game.
    Vector *position = nullptr;
    // Object of the player of the game.
    GameObject *player = nullptr;
    // Object for the positions of the player.
    Vector playerPosition = Vector(0,0);

    // Timer for the first attack cooldown.
    Timer timerFirstAttackCooldown;
    // Timer for when the first attack has gone.
    Timer timerFirstAttackGone;
    // Timer for a attack cooldown.
    Timer timerAttackCooldown;
    // Timer for the second attack cooldown.
    Timer timerSecondAttack;
    // Timer for the second attack fall.
    Timer timerSecondAttackFall;

    // Stores if is the first attack of the first boss.
    bool FirstAttack = false;
    // Stores if the first attack of the first boss has gone.
    bool goneFirstAttack = false;
    // Stores if is the second attack of the first boss.
    bool SecondAttack = false;
    // Stores if is the jump in the second attack of the first boss.
    bool SecondAttackJump = false;
    // Stores if is the second attack of the first boss has fallen.
    bool SecondAttackFall = false;

    // Stores if the camera is shaking.
    bool shake = false;

    // Stores the number of first attacks.
    int firstAttackCounter = 0;
    // Stores a random integer number.
    int randNum = -1;
};

#endif
