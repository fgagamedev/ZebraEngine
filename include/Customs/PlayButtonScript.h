#ifndef __PLAY_BUTTON_SCRIPT__
#define __PLAY_BUTTON_SCRIPT__

#include "Components/Script.h"
#include "Components/UIButton.h"
#include "Log/log.h"

using namespace std;

class PlayButtonScript : public Script {
public:
  PlayButtonScript(GameObject *owner);
  string GetComponentName() override { return "PlayButtonScript"; };
  void ComponentUpdate() override;
  void Start() override;

private:
  UIButton *buttonComponent = nullptr;
};

#endif
