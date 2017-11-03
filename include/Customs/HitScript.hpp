/**
    @file HitScripr.hpp
    @brief Responsible for organizing sound effects script.
    @copyright MIT License.
*/

#ifndef __HIT_SCRIPT__
#define __HIT_SCRIPT__

#include "Components/Animator.hpp"
#include "Components/Script.hpp"

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/Timer.hpp"

#include "Math/Vector.hpp"

#include <string>

class HitScript : public Script {

    public:

        HitScript(GameObject *owner);

        std::string GetComponentName() override {
            return "HitScript";
        };

        void FixedComponentUpdate() override;

        void Start() override;


    private:

        bool m_hit = false;

        int m_hitLevel = 0;

        void CreateAnimations();

        InputSystem *m_input = nullptr;

        Animator *m_animator = nullptr;

        Vector *m_position = nullptr;

        void ComponentUpdate() override;

};

#endif
