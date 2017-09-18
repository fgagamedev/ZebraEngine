#ifndef __CREDITS_SCRIPT__
#define __CREDITS_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Customs/NakedManScript.hpp"
#include "Components/Animator.hpp"
#include "Components/RectangleRenderer.hpp"
#include "Components/UIText.hpp"
#include "Components/Script.hpp"
#include "Customs/FirstBossController.hpp"
#include "Math/Vector.hpp"

#include <string>

class CreditsScript : public Script {

public:
    CreditsScript(GameObject *owner);
    std::string GetComponentName() override { return "CreditsScript"; };
    void FixedComponentUpdate() override;
    void Start() override;

protected:
    void ComponentUpdate() override;

private:
    Vector *position = nullptr;

};

#endif
