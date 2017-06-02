#ifndef __SCRIPT__
#define __SCRIPT__

#include <utility>

#include "Engine/Component.h"
#include "Engine/GameObject.h"

class Script : public Component {
public:
  // constructor and destructor
  Script(GameObject *owner);
  // pure virtual name getter
  virtual std::string GetComponentName() = 0;
};

#endif // __SCRIPT__
