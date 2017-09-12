#ifndef __PRE_MENU_SCENE__
#define __PRE_MENU_SCENE__

#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Image.hpp"

#include "Components/Animator.hpp"
#include "Components/Animation.hpp"


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
