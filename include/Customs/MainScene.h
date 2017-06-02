#ifndef __MAIN_SCENE__
#define __MAIN_SCENE__

#include "Components/UIButton.h"
#include "Components/UIText.h"
#include "Customs/PlayButtonScript.h"
#include "Customs/QuitButtonScript.h"
#include "Engine/GameObject.h"
#include "Engine/Scene.h"

class MainScene : public Scene {
public:
  virtual void OnActivation() override;
  virtual void OnDeactivation() override;
  virtual void OnShown() override;
  virtual void OnHidden() override;

private:
  void CreateLogo();
  void CreatePlayButton();
  void CreateQuitButton();
};

#endif
