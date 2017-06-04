#ifndef __CATCH_ALL_BUTTON_SCRIPT__
#define __CATCH_ALL_BUTTON_SCRIPT__

#include "Components/Script.h"
#include "Components/UIButton.h"
#include "Customs/MenuController.h"
#include "Log/log.h"
#include "Components/UIText.h"




using namespace std;

class CatchAllButtonScript : public Script {
public:
  CatchAllButtonScript(GameObject *owner);
  virtual void Start() override;
  virtual void ComponentUpdate() override;
  virtual string GetComponentName() override { return "CatchAllButtonScript"; };

private:
  UIButton *m_uiButton = nullptr;
  GameObject *m_checkbox = nullptr;
};

#endif
