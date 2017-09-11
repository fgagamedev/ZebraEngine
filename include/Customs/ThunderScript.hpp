#ifndef __THUNDER_SCRIPT__
#define __THUNDER_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

class ThunderScript : public Script {
public:
    ThunderScript(GameObject *owner);
    std::string GetComponentName() override {
        return "ThunderScript";
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
    int play=0;

};
#endif
