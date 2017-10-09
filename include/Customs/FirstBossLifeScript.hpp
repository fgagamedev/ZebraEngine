/**
    @file FirstBossLifeScript.hpp
    @brief Manage the first boss life.
    @copyright MIT License.
*/
#ifndef __FIRST_BOSS_LIFE_SCRIPT__
#define __FIRST_BOSS_LIFE_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/RectangleRenderer.hpp"
#include "Customs/FirstBossController.hpp"
#include "Components/UIText.hpp"
#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Customs/NakedManScript.hpp"
#include "Math/Vector.hpp"

#include <string>

class FirstBossLifeScript : public Script {

public:
    FirstBossLifeScript(GameObject *owner);

    // Get the component name and replace it by returning its string name.
    std::string GetComponentName() override {
        return "FirstBossLifeScript";
    };
    void FixedComponentUpdate() override;
    void Start() override;

    // Boolean variable that is responsible for saying whether or not.
    bool hit = false;

private:

    // Pointer position that stores the vector position of the boss's attack.
    Vector *position = nullptr;

protected:
    void ComponentUpdate() override;

};

#endif
