#ifndef __MISSILE_BUTTON_SCRIPT__
#define __MISSILE_BUTTON_SCRIPT__

#include "Components/Script.h"
#include "Components/UIButton.h"
#include "Customs/MenuController.h"

using namespace std;

class MissileButtonScript : public Script {
public:
  MissileButtonScript(GameObject *owner);
  virtual void Start() override;
  virtual void ComponentUpdate() override;
  virtual string GetComponentName() override { return "MissileButtonScript"; };

private:
  UIButton *m_uiButton = nullptr;
  GameObject *m_checkbox = nullptr;
};

#endif
