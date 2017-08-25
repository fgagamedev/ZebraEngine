#ifndef __MENU_ANIMATION_SCRIPT__
#define __MENU_ANIMATION_SCRIPT__

#include "Engine/SceneManager.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"


class MenuAnimationScript : public Script {
public:
  MenuAnimationScript (GameObject *owner);
  std::string GetComponentName() override { return "MenuAnimationScript"; };
  void FixedComponentUpdate() override;
  void Start() override;



protected:
  void ComponentUpdate() override;

private:
    bool initialanimation=false;
    int currentframe=0;
    bool isPlaying=false;
  void CreateAnimations();
  Animator *animator = nullptr;
  Vector *position = nullptr;


};

#endif
