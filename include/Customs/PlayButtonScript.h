#ifndef __PLAY_BUTTON_SCRIPT__
#define __PLAY_BUTTON_SCRIPT__

#include "Components/Script.h"
#include "Components/UIButton.h"
#include "Components/UIText.h"
#include "Components/UISound.h"
#include "Engine/GameObject.h"

using namespace std;

class PlayButtonScript : public Script {
public:
  PlayButtonScript(GameObject *owner);
  string GetComponentName() override { return "PlayButtonScript"; };
  void ComponentUpdate() override;
  void Start() override;

private:
  UIButton *m_uiButton = nullptr;
};
#endif
