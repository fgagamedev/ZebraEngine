#ifndef __PRE_MENU_SCENE__
#define __PRE_MENU_SCENE__

#include "Engine/GameObject.h"
#include "Engine/Scene.h"
#include "Engine/Image.h"
#include "Components/Animator.h"
#include "Components/Animation.h"


class PreMenuScene : public Scene {
public:
  void OnActivation() override;
  void OnDeactivation() override;
  void OnShown() override;
  void OnHidden() override;

private:
void CreateLogoSdl();
void CreateLogoUnb();
void CreateLogoControle();
void CreateLogoZebra();

};

#endif