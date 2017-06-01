#include "Engine/CollisionSystem.h"
#include <math.h>
CollisionSystem *CollisionSystem::m_instance = nullptr;

CollisionSystem::CollisionSystem() {}

CollisionSystem *CollisionSystem::GetInstance() {
  if (!m_instance)
    m_instance = new CollisionSystem();
  return m_instance;
}

void CollisionSystem::Update() {
  PushColliders();
  DetectCollisions();
}

void CollisionSystem::DetectCollisions() {
  for (int i = 0; i < m_colliders.size(); i++) {
    for (int k = i + 1; k < m_colliders.size(); k++) {
      if (m_colliders[i]->GetComponentName() ==
              m_colliders[k]->GetComponentName() &&
          m_colliders[i]->GetComponentName() == "CircleCollider")
        CircleCircle((CircleCollider *)m_colliders[i],
                     (CircleCollider *)m_colliders[k]);

      else if (m_colliders[i]->GetComponentName() ==
                   m_colliders[k]->GetComponentName() &&
               m_colliders[i]->GetComponentName() == "RectangleCollider")
        RectRect((RectangleCollider *)m_colliders[i],
                 (RectangleCollider *)m_colliders[k]);

      else if (m_colliders[i]->GetComponentName() !=
                   m_colliders[k]->GetComponentName() &&
               m_colliders[i]->GetComponentName() == "CircleCollider")
        CircleRect((CircleCollider *)m_colliders[i],
                   (RectangleCollider *)m_colliders[k]);

      else
        CircleRect((CircleCollider *)m_colliders[k],
                   (RectangleCollider *)m_colliders[i]);
    }
  }
}

void CollisionSystem::PushColliders() {
  m_colliders.clear();

  auto gameobjects =
      SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();

  for (auto gameobject : gameobjects) {
    for (auto key : gameobject->GetAllComponents()) {
      if (key.first != C_PHYSICS)
        break;
      for (auto element : key.second) {
        if (element->GetComponentName() == "CircleCollider" ||
            element->GetComponentName() == "RectangleCollider")
          m_colliders.push_back((Collider *)element);
      }
    }
  }
}

void CollisionSystem::CircleCircle(CircleCollider *c1, CircleCollider *c2) {
  bool collision = false;
  auto c2Center = c2->GetCenter();
  if (c1->GetCenter().GetDistance(c2Center) <=
      c1->GetRadius() + c2->GetRadius())
    collision = true;

  if (collision) {
    INFO("CIRCLE CIRCLE");
    INFO("COLLIDED");
  }
}

void CollisionSystem::RectRect(RectangleCollider *r1, RectangleCollider *r2) {
  bool collision = false;
  auto posR1 = r1->GetRectanglePoint();
  auto posR2 = r2->GetRectanglePoint();

  if (abs(posR1.m_x - posR2.m_x) * 2 <= r1->GetWidth() + r2->GetWidth() &&
      abs(posR1.m_y - posR2.m_y) * 2 <= r1->GetHeight() + r2->GetHeight())
    collision = true;

  if (collision) {
    INFO("COLLIDED");
    INFO("RECT RECT");
  }
}

void CollisionSystem::CircleRect(CircleCollider *c, RectangleCollider *r) {
    bool collision = false;
    //Distance between centers in x-axis
    double distX = abs(c->GetCenter().m_x - r->GetRectanglePoint().m_x - r->GetWidth()/2 );
    //Distance between centers in y-axis
    double distY = abs(c->GetCenter().m_y - r->GetRectanglePoint().m_y - r->GetHeight()/2 );
    //Distance between centers  in x-axis
    double dx=distX - r->GetWidth()/2;
    double dy=distY - r->GetHeight()/2;
    //Checks if the distance on x-axis between centers are greater than RectWidth/2 + CircleRadius,in that case
    //there is no Collision.The same logic is used on y-axis
     if (!((distX > (r->GetWidth()/2 + c->GetRadius())) || (distY > (r->GetHeight()/2 + c->GetRadius()) )))
        /*verify if the distance between centers are lesser than rect width and height,
         also checks if the hypotenuse(Line that connects both centers and crosses
        the rect vertice) is lesser than circle radius^2,in that case,collision occurs.*/
        if (((distX <= (r->GetWidth()/2)) || (distY <= (r->GetHeight()/2))) || (dx*dx + dy*dy <= (c->GetRadius()*c->GetRadius())))
                collision=true;
  if (collision) {
    INFO("COLLIDED");
    INFO("RECT CIRCLE");
  }

}
