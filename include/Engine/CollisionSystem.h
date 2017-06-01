#ifndef __COLLISION_SYSTEM__
#define __COLLISION_SYSTEM__

#include <math.h>
#include <vector>

#include "Components/CircleCollider.h"
#include "Components/Collider.h"
#include "Components/RectangleCollider.h"
#include "Engine/SceneManager.h"
#include "Log/log.h"

#include "Math/Vector.h"

using namespace std;

class CollisionSystem {
public:
  static CollisionSystem *GetInstance();
  void Update();

private:
  CollisionSystem();
  void DetectCollisions();
  void PushColliders();
  void CircleCircle(CircleCollider *c1, CircleCollider *c2);
  void RectRect(RectangleCollider *r1, RectangleCollider *r2);
  void CircleRect(CircleCollider *c, RectangleCollider *r);

  static CollisionSystem *m_instance;
  vector<Collider *> m_colliders;
};

#endif
