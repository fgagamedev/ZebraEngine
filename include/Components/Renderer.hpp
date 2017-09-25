/**
    @file Renderer.hpp
    @brief Manages renderings of images on the screen.
    @copyright LGPL. MIT License.
*/

#ifndef __RENDERER__
#define __RENDERER__

#include "Engine/Component.hpp"
#include "Engine/Image.hpp"

#include "Math/Vector.hpp"

#include <utility>

class Renderer : public Component {
public:
    // Constructor and destructor
    Renderer(GameObject *owner, Image *img);
    ~Renderer();

    // Replace the component name and return it.
    inline std::string GetComponentName() override {
        return "Renderer";
    };

    // Getter for image
    inline Image *GetImage() {
        return m_image;
    };

    // Image handling
    void Rotate(double angles);
    void RotateTowards(Vector *point);

    // Override for start
    void Start() override;
    void SetActivationTrue() {
        activation = true;
    };
    void SetActivationFalse() {
        activation = false;
    };

protected:
    // Overriding method called by final update
    void ComponentUpdate() override;

private:
    // Boolean attribute to track the activation of the renderer
    bool activation = true;

    // Rectangle's image pointer to be renderer on the screen
    Image *m_image = nullptr;

    // Position vector of the Renderer
    Vector *m_position = nullptr;
};

#endif // __RENDERER__
