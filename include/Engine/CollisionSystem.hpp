#ifndef __COLLISION_SYSTEM__
#define __COLLISION_SYSTEM__

#include "Engine/SceneManager.hpp"

#include "Components/CircleCollider.hpp"
#include "Components/Collider.hpp"
#include "Components/RectangleCollider.hpp"
#include "Log/log.hpp"
#include "Math/Vector.hpp"

#include <math.h>
#include <vector>

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
