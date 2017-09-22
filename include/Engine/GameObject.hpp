/**
    @file GameObject.hpp
    @brief Class that represents all the game objects, like name and velocity.
    @copyright LGPL. MIT License.
*/

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Engine/Component.hpp"
#include "Engine/sdl2include.hpp"

#include "Globals/ComponentTypes.hpp"
#include "Math/Vector.hpp"

#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


class GameObject {
public:
    // Active atribbute
    bool active = true;
  
    // Constructor and destructor
    GameObject(std::string name, Vector *position = new Vector(0, 0),
               int width = 0, int height = 0, Uint8 layer = 0);
    ~GameObject();

    // Method for handling start and updates
    void Start();
    void Update();
    void FixedUpdate();
    void DrawUpdate();

    // Components management
    void AddComponent(Component *component);
    void AddComponent(std::vector<Component *> components);
    Component *GetComponent(std::string name);
    std::unordered_map<Uint32, std::vector<Component *>> GetAllComponents() {
      return m_components;
    };

    std::string GetName() { return m_name; };

    // Getter and setter
    inline Vector *GetPosition() { return m_position; };
    inline void SetPosition(Vector value) { *m_position = value; };
    inline void SetZoomProportion(Vector value) { *zoomProportion = value;};
    inline int GetWidth() { return m_width; };
    inline void SetWidth(int width) {this->m_width = width; };
    inline int GetHeight() { return m_height; };
    inline Vector *GetZoomProportion() { return zoomProportion; };
    void SetSize(int width, int height);
  
    //Object Tag
    inline void SetTag(std::string tag) { m_tag = tag; };
    inline std::string GetTag() { return m_tag; };
  
    inline Uint8 GetLayer() { return m_layer; };
    Vector GetVelocity();

    // Operator overload
    bool operator<(const GameObject &go) const;

    // Velocity
    void AddVelocity(Vector velocity);

    // Sets width and height of a gameobject.
    float originalWidth;
    float originalHeight;
  
    // Collision
    void AddCollision(GameObject *gameobject);
    void ClearCollisions();
    std::vector<GameObject *> GetCollisions();

    // Sets the position of a gameobject, type vector.
    Vector *m_position = new Vector(0, 0);
  
private:
    // Map of components
    std::unordered_map<Uint32, std::vector<Component *>> m_components;
    
    // Object properties
    std::string m_name = "no_name_defined";

    // Sets the width of a gameobject.
    int m_width = 0;

    // Sets the height of a gameobject.
    int m_height = 0;
 
    Vector *zoomProportion = new Vector(1,1);

    //An unsigned 8-bit integer type sets the gameobject's layer.
    Uint8 m_layer;
    std::string m_tag = "";

    //Sets the velocity of the gameobject, type vector.
    Vector *m_velocity;

    //Sets a vector for gameobject's collisions.
    std::vector<GameObject *> m_colliding;
  
    // Methods for handling specific update
    void PhysicsUpdate();
    void ComponentsUpdate();
};

#endif // __GAME_OBJECT__
