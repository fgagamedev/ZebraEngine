/**
    @file PlayerAttackScript.hpp
    @brief Class that represents the Script of the player attack 
    @copyright LGPL. MIT License.
*/

#ifndef __PLAYER_ATTACK_SCRIPT__
#define __PLAYER_ATTACK_SCRIPT__

#include "Engine/GraphicsSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Renderer.hpp"
#include "Components/RectangleCollider.hpp"
#include "Components/Animator.hpp"
#include "Customs/FirstBossLifeScript.hpp"
#include "Customs/AudioController.hpp"
#include "Math/Vector.hpp"

#include <string>


class PlayerAttackScript : public Script {

public:
    PlayerAttackScript(GameObject *owner);
    std::string GetComponentName() override { return "PlayerAttackScript"; };
    void FixedComponentUpdate() override;
    void Start() override;
    void SetShoot(bool shoot);
    void GameCollisionCheck();

protected:
    void ComponentUpdate() override;
private:
    void CreateAnimations();

    // Instantiating input system of the keyboard. 
    InputSystem *input = nullptr;

    // Instantiating animations.
    Animator *animator = nullptr;

    // Instantiating vector.
    Vector *position = nullptr;

    // Instantiating collisions system.
    RectangleCollider* playerCollider =  nullptr;

    // Instantiating mouse and player positions.
    Vector mousePosition = Vector(0,0);
    Vector playerPosition = Vector(0,0);

    // Instantiating gameobject, it brings all the fundamental game functionalities.
    GameObject *player = nullptr;

    //State of a shoot.
    bool shoot = false;

    //State of the script.
    int play=0;

    // Angle of a shot bullet.
    float angle=0;

    // Vector of bullets position.
    Vector bulletVelocity = Vector(0, 0);

    // Speed of a shot bullet.
    float bulletSpeed = 30;
};

#endif
