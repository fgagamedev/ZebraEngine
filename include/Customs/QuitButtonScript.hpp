#ifndef __QUIT_BUTTON_SCRIPT__
#define __QUIT_BUTTON_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SDLSystem.hpp"

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"

using namespace std;

class QuitButtonScript : public Script {
public:
  QuitButtonScript(GameObject *owner);
  string GetComponentName() override { return "QuitButtonScript"; };
  void ComponentUpdate() override;
  void Start() override;

private:
  UIButton *m_uiButton = nullptr;
};
#endif
