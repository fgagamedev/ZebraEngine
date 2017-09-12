#ifndef __RAIN_SCRIPT__
#define __RAIN_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Customs/AudioController.hpp"
#include "Math/Vector.hpp"

#include <string>

class RainScript : public Script {

public:
  RainScript(GameObject *owner);
  std::string GetComponentName() override { return "RainScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
int play=0;
protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;


};

#endif
