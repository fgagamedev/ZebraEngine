#include "Engine/GameObject.hpp"

#include "Log/log.hpp"

GameObject::GameObject(std::string name, Vector *position,
    int width, int height, Uint8 layer) {
    m_name = name;
    m_position = position;
    m_width = width;
    m_height = height;
    m_layer = layer;
    m_velocity = new Vector(0, 0);
    originalWidth = width;
    originalHeight = height;
}

GameObject::~GameObject() {
    delete m_position;
    delete m_position;
}

/**
    @brief that function starts the game. Checks if the key is on begins and
    if the key is diferent of the end.
*/
void GameObject::Start() {
    for (auto key = m_components.begin(); key != m_components.end(); key++) {
        for (auto component : key->second) {
            component->Start();
    }
  }
}

/**
    @brief that function updates all the components of the game objects.
*/
void GameObject::Update() { ComponentsUpdate(); }

/**
    @brief that function updates all the draw components. Find the draws, check
    if is active and update the component.
*/
void GameObject::DrawUpdate() {
    auto it = m_components.find(C_DRAW);

    if (it != m_components.end()) {
        for (auto component : it->second) {
            if (component->active) {
                component->Update();
            }
        }
    }
}

/**
    @brief that function updates all the physics components. Find the pyhsics
    components, check if is active and update the component.
*/
void GameObject::PhysicsUpdate() {
    auto it = m_components.find(C_PHYSICS);

    if (it != m_components.end()) {
        for (auto component : it->second) {
            if (component->active) {
                component->Update();
            }
        }
    }
}

/**
    @brief that function updates all the general components. Find the common, check
    if is active and update the component.
*/
void GameObject::ComponentsUpdate() {
    auto it = m_components.find(C_COMMON);

        if (it != m_components.end()) {
            for (auto component : it->second) {
                if (component->active) {
                    component->Update();
            }
          }
        }
}

void GameObject::AddComponent(Component *component) {
    auto type = component->GetType();
    auto it = m_components.find(type);

    if (it != m_components.end()) {
        it->second.push_back(component);
    } else {
        m_components.emplace(type, std::vector<Component *>());
        m_components.at(type).push_back(component);
    }
}

void GameObject::AddComponent(std::vector<Component *> components) {
    for (auto it : components) {
        AddComponent(it);
    }
}

Component *GameObject::GetComponent(std::string name) {
    for (auto key = m_components.begin(); key != m_components.end(); key++) {
        for (auto value : key->second) {
            if (value->GetComponentName() == name) {
                return value;
            }
        }
    }
 // INFO("Looking for null component " << name);
    return nullptr;
}

void GameObject::FixedUpdate() {
    for (auto key = m_components.begin(); key != m_components.end(); key++) {
        for (auto value : key->second) {
            value->FixedComponentUpdate();
        }
    }
  PhysicsUpdate();
}

/**
    @brief that function set the size based on width and height.
    @param[in] width and height in centimeters. Both are poiting for their self.

*/
void GameObject::SetSize(int width, int height{
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

void GameObject::AddCollision(GameObject *gameobject) {
    m_colliding.push_back(gameobject);
}

void GameObject::ClearCollisions() { m_colliding.clear(); }

std::vector<GameObject *> GameObject::GetCollisions() { return m_colliding; }
