/**
    @file Rigidbody.hpp
    @brief This class defines gravity an its intesity in the game.
    @copyright LGPL. MIT License.
*/

#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"

#include <string>

class Rigidbody : public Component {
public:
    Rigidbody(GameObject *owner);
    std::string GetComponentName() override { return "Rigidbody"; };
    void FixedComponentUpdate() override;
    inline void SetGravityForce(int force) { m_gravityForce = force; };

private:
    // Sets a bool to represent gravity's state.
    bool m_gravity = true;

    // Sets a float to represent gravity's force.
    float m_gravityForce = 0.4;
};

#endif
