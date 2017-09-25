#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "Engine/Component.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Renderer.hpp"

#include <string>

/**
    @file UIButton.hpp
    @brief Class that manages all game's buttons as 'quit' and 'start'.
    @copyright LGPL. MIT License.
*/


class UIButton : public Component {
    public:

        // Constructor and destructor
        UIButton(GameObject *owner);
        ~UIButton();

        // Overrides
        std::string GetComponentName() override {
            return "UIButton";
        };
        void Start() override;

        // UIButton methods
        bool IsClicked();
        bool IsOver();

    private:
        Vector *m_position = nullptr;
};

#endif // __UI_BUTTON__
