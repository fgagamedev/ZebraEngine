#ifndef __LIGHT_SCRIPT__
#define __LIGHT_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

class LightScript : public Script {

public:
  LightScript(GameObject *owner);
  std::string GetComponentName() override { return "RainScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  GameObject *player = nullptr;
  int play=1;

};

#endif
