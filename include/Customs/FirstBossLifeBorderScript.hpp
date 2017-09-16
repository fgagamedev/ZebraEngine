/**
    @file FirstBossLifeBorderScript.cpp
    @brief Class that defines methods and attributes for 
    activating the first boss life border script.
    @copyright LGPL. MIT License.
*/
#ifndef __FIRST_BOSS_LIFE_BORDER_SCRIPT__
#define __FIRST_BOSS_LIFE_BORDER_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/RectangleRenderer.hpp"
#include "Components/UIText.hpp"
#include "Components/Script.hpp"
#include "Customs/NakedManScript.hpp"
#include "Math/Vector.hpp"

#include <string>

class FirstBossLifeBorderScript : public Script {

    public:
        FirstBossLifeBorderScript(GameObject *owner);
        std::string GetComponentName() override {
            return "FirstBossLifeBorderScript"; 
        };
        void FixedComponentUpdate() override;
        void Start() override;
        void CreateAnimations();

    protected:
    void ComponentUpdate() override;

    private:
    Vector *position = nullptr;
    InputSystem *input = nullptr;
    Animator *animator = nullptr;
    RectangleCollider* firstBossAttackCollider = nullptr;
};

#endif
