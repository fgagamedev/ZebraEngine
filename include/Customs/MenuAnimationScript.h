#ifndef __MENU_ANIMATION_SCRIPT__
#define __MENU_ANIMATION_SCRIPT__

#include "Components/Animator.h"
#include "Components/Script.h"
#include "Engine/SceneManager.h"


class MenuAnimationScript : public Script {
public:
  MenuAnimationScript (GameObject *owner);
  std::string GetComponentName() override { return "MenuAnimationScript"; };
  void FixedComponentUpdate() override;
  void Start() override;



protected:
  void ComponentUpdate() override;

private:
    int currentframe=0;
    bool isPlaying=false;
  void CreateAnimations();
  Animator *animator = nullptr;
  Vector *position = nullptr;


};

#endif
