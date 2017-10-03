/**
    @file Component.hpp
    @brief Manage the components of the game.
	@copyright MIT License.
*/

#ifndef __COMPONENT__
#define __COMPONENT__

#include "Globals/ComponentTypes.hpp"

#include <string>

class GameObject;

class Component {
    public:
        // active attribute
        bool active = true;

        // constructor and destructor
        Component(GameObject *owner, ComponentType type);
        ~Component();
        // getters and setters
        virtual inline ComponentType GetType() final {
            return m_type;
        };
        virtual inline void SetOwner(GameObject *gameObject) final {
            m_owner = gameObject;
        };
        virtual inline GameObject *GetOwner() {
            return m_owner;
        };
        // unoverridable update
        virtual void Update() final;
        // method for getting the component name
        virtual std::string GetComponentName() = 0;
        // Start method
        virtual void Start(){};
        virtual void FixedComponentUpdate(){};
        virtual void ComponentUpdate(){};

        // Component type.
        ComponentType m_type;

    private:
        // GameObject that owns the component.
        GameObject *m_owner;
};

#endif // __COMPONENT__
