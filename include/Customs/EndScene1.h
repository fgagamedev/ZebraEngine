#ifndef __END_SCENE1__
#define __END_SCENE1__

#include "Components/RectangleRenderer.h"
#include "Components/Renderer.h"
#include "Components/UIButton.h"
#include "Components/UIText.h"
#include "Components/UISound.h"
#include "Customs/CatchAllButtonScript.h"
#include "Customs/MissileButtonScript.h"
#include "Customs/PlayButtonScript.h"
#include "Customs/QuitButtonScript.h"
#include "Engine/Image.h"
#include "Engine/Scene.h"
#include "Globals/EngineGlobals.h"

class EndScene1 : public Scene {
public:
  EndScene1();
  virtual void OnActivation() override;
  virtual void OnDeactivation() override;
  virtual void OnShown() override;
  virtual void OnHidden() override;

private:
  void CreateGameOver();
  void CreateQuitButton();
  int m_width_middle;
  int m_height_middle;

};

#endif
