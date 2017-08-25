#ifndef __RECTANGLE_RENDERER__
#define __RECTANGLE_RENDERER__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Math/Vector.hpp"

#include <string>

using namespace std;

class RectangleRenderer : public Component {
public:
    RectangleRenderer(GameObject *owner, Vector offset, int width, int height);
    void SetColor(int red, int green, int blue, int alpha);
    virtual string GetComponentName() override { return "RectangleRenderer"; };
    virtual void ComponentUpdate() override;
    inline void SetWidth(int width) { this->m_width = width; };
    inline int GetWidth() { return m_width; };
private:
    int m_width = 0, m_height = 0;
    int m_red = 0, m_green = 0, m_blue = 255, m_alpha = 255;
    Vector m_offset;    
};

#endif
