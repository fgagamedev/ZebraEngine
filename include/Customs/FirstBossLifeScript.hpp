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
  std::string GetComponentName() override { return "FirstBossLifeScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  bool hit =  false;


protected:
  void ComponentUpdate() override;
private:
  Vector *position = nullptr;




};

#endif
