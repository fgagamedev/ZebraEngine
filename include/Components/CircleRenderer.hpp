/**
    @file CircleRenderer.hpp
    @brief Manage circles rendered in the game.
    @copyright MIT License.
*/

#ifndef __CIRCLE_RENDERER__
#define __CIRCLE_RENDERER__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Math/Vector.hpp"

#include <string>

using namespace std;

class CircleRenderer : public Component {
public:
    // Instances and manages colors, information, and creates CircleRenderer.
    CircleRenderer(GameObject *owner, Vector offset, float radius);
    void SetColor(int red, int green, int blue, int alpha);
    virtual string GetComponentName() override {
        return "CircleRenderer";
    };
    virtual void ComponentUpdate() override;
private:
    //Red color integer value. The initialize in 0.
    int m_red = 0;

    //Green color integer value. The initialize in 0.
    int m_green = 0;

    //Blue color integer value. The initialize in 255.
    int m_blue = 255;

    /*Transparency integer value. The initialize in 255, and
      the lower is the value, bigger is the transparency.*/
    int m_alpha = 255;

    //Radius to render the circle
    float m_radius = 0;

    //Responsible for printing the circle
    Vector m_offset;
};

#endif
