/**
    @file FirstBossLifeScript.cpp
    @brief Manage the animations for the first boss central effect.
    @copyright MIT License.
*/
#ifndef _BOSS_1_CENTRAL_SCRIPT__
#define _BOSS_1_CENTRAL_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class FirstBossCentralEffectScript : public Script {
public:
    FirstBossCentralEffectScript(GameObject *owner);
    std::string GetComponentName() override {
        return "FirstBossCentralEffectScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

private:
    void CreateAnimations();

    // Pointer to game controls
    InputSystem *m_input = nullptr;

    // Pointer to animator game.
    Animator *m_animator = nullptr;

    // Poiter to position of gamer.
    Vector *m_position = nullptr;

    // Poiter to object boss.
    GameObject *m_boss = nullptr;

protected:
    void ComponentUpdate() override;

};
#endif
