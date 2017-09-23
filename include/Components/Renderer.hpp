#ifndef __RENDERER__
#define __RENDERER__

#include "Engine/Component.hpp"
#include "Engine/Image.hpp"

#include "Math/Vector.hpp"

#include <utility>

class Renderer : public Component {
public:
    // constructor and destructor
    Renderer(GameObject *owner, Image *img);
    ~Renderer();
    // overriding method for getting component name
    inline std::string GetComponentName() override {
        return "Renderer";
    };
    // getter for image
    inline Image *GetImage() { 
        return m_image; 
    };
    // image handling
    void Rotate(double angles);
    void RotateTowards(Vector *point);
    // override for start
    void Start() override;
    void SetActivationTrue() {
        activation = true;
    };
    void SetActivationFalse() {
        activation = false;
    };

protected:
    // overriding method called by final update
    void ComponentUpdate() override;

private:
    bool activation = true;
    Image *m_image = nullptr;
    Vector *m_position = nullptr;
};

#endif // __RENDERER__
