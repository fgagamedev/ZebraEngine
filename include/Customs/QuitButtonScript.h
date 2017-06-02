#ifndef __QUIT_BUTTON_SCRIPT__
#define __QUIT_BUTTON_SCRIPT__

#include "Components/Script.h"
#include "Components/UIButton.h"
#include "Engine/SDLSystem.h"

using namespace std;

class QuitButtonScript : public Script {
public:
  QuitButtonScript(GameObject *owner);
  string GetComponentName() override { return "QuitButtonScript"; };
  void ComponentUpdate() override;
  void Start() override;

private:
  UIButton *buttonComp = nullptr;
};

#endif
