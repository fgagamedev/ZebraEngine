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

protected:
    void ComponentUpdate() override;

private:
    void CreateAnimations();
    InputSystem *input = nullptr;
    Animator *animator = nullptr;
    Vector *position = nullptr;
    GameObject *boss = nullptr;
};
#endif
