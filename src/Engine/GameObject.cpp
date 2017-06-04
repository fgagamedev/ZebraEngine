#include "Engine/GameObject.h"
#include "Log/log.h"

GameObject::GameObject(std::string name, Vector *position, int width,
                       int height, Uint8 layer) {
  m_name = name;
  m_position = position;
  m_width = width;
  m_height = height;
  m_layer = layer;
  m_velocity = new Vector(0, 0);
}

GameObject::~GameObject() {
  delete m_position;
  delete m_position;
}

void GameObject::Start() {
  for (auto key = m_components.begin(); key != m_components.end(); key++) {
    for (auto component : key->second) {
      component->Start();
    }
  }
}

void GameObject::Update() { ComponentsUpdate(); }

void GameObject::DrawUpdate() {
  auto it = m_components.find(C_DRAW);

  if (it != m_components.end())
    for (auto component : it->second)
      if (component->active)
        component->Update();
}

void GameObject::PhysicsUpdate() {
  auto it = m_components.find(C_PHYSICS);

  if (it != m_components.end())
    for (auto component : it->second)
      if (component->active)
        component->Update();
}

void GameObject::ComponentsUpdate() {
  auto it = m_components.find(C_COMMON);

  if (it != m_components.end())
    for (auto component : it->second)
      if (component->active)
        component->Update();
}

void GameObject::AddComponent(Component *component) {
  auto type = component->GetType();
  auto it = m_components.find(type);

  if (it != m_components.end())
    it->second.push_back(component);
  else {
    m_components.emplace(type, std::vector<Component *>());
    m_components.at(type).push_back(component);
  }
}

void GameObject::AddComponent(std::vector<Component *> components) {
  for (auto it : components)
    AddComponent(it);
}

Component *GameObject::GetComponent(std::string name) {
  for (auto key = m_components.begin(); key != m_components.end(); key++) {
    for (auto value : key->second) {
      if (value->GetComponentName() == name)
        return value;
    }
  }
 // INFO("Looking for null component " << name);
  return nullptr;
}

void GameObject::FixedUpdate() {
  for (auto key = m_components.begin(); key != m_components.end(); key++) {
    for (auto value : key->second)
      value->FixedComponentUpdate();
  }

  PhysicsUpdate();
}

void GameObject::SetSize(int width, int height) {
  m_width = width;
  m_height = height;
}

bool GameObject::operator<(const GameObject &go) const {
  return m_layer < go.m_layer;
}

void GameObject::AddVelocity(Vector velocity) {
  m_velocity->m_x += velocity.m_x;
  m_velocity->m_y += velocity.m_y;
}

Vector GameObject::GetVelocity() { return *m_velocity; }
