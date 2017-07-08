#ifndef __END_SCENE2__
#define __END_SCENE2__

#include "Components/RectangleRenderer.h"
#include "Components/Renderer.h"
#include "Components/UIButton.h"
#include "Components/UIText.h"
#include "Components/UISound.h"
#include "Customs/CatchAllButtonScript.h"
#include "Customs/MissileButtonScript.h"
#include "Customs/PlayButtonScript.h"
#include "Customs/QuitButtonScript.h"
#include "Customs/GameOverScript.h"
#include "Engine/Image.h"
#include "Engine/Scene.h"
#include "Globals/EngineGlobals.h"

class EndScene2 : public Scene {
public:
  EndScene2();
  virtual void OnActivation() override;
  virtual void OnDeactivation() override;
  virtual void OnShown() override;
  virtual void OnHidden() override;

private:
  void CreateAnimation();
  int m_width_middle;
  int m_height_middle;
  void CreateQuitButton();


};

#endif
