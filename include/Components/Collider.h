#ifndef __COLLIDER__
#define __COLLIDER__

#include "Engine/Component.h"

using namespace std;

class Collider : public Component {
public:
  Collider(GameObject *owner, int layer) : Component(owner, C_PHYSICS) {
    m_layer = layer;
  };
  virtual int GetLayer() final { return m_layer; };

private:
  int m_layer;
};

#endif
