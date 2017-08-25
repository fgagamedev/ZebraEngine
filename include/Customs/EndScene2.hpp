#ifndef __END_SCENE2__
#define __END_SCENE2__

#include "Engine/Image.hpp"
#include "Engine/Scene.hpp"

#include "Components/RectangleRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"
#include "Customs/CatchAllButtonScript.hpp"
#include "Customs/MissileButtonScript.hpp"
#include "Customs/PlayButtonScript.hpp"
#include "Customs/QuitButtonScript.hpp"
#include "Customs/GameOverScript.hpp"
#include "Globals/EngineGlobals.hpp"

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
