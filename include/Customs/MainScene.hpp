#ifndef __MAIN_SCENE__
#define __MAIN_SCENE__

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
#include "Globals/EngineGlobals.hpp"

class MainScene : public Scene {
public:
  MainScene();
  virtual void OnActivation() override;
  virtual void OnDeactivation() override;
  virtual void OnShown() override;
  virtual void OnHidden() override;

private:
  void CreateAnimation();
  int m_width_middle;
  int m_height_middle;
  void CreateLogo();
  void CreatePlayButton();
  void CreateQuitButton();

  void CreateMusic();
  //void CreateBackground();
  //void CreateGamemodes();

};

#endif
