#ifndef __CATCH_ALL_BUTTON_SCRIPT__
#define __CATCH_ALL_BUTTON_SCRIPT__

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Customs/MenuController.hpp"
#include "Components/UIText.hpp"
#include "Log/log.hpp"


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
