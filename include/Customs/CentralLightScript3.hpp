#ifndef __CENTRAL_LIGHT_SCRIPT3__
#define __CENTRAL_LIGHT_SCRIPT3__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

class CentralLightScript3 : public Script {

    public:

        CentralLightScript3(GameObject *owner);

        std::string GetComponentName() override {
            return "CentralLightScript3";
        };

        void FixedComponentUpdate() override;

        void Start() override;

        void Activate(){
            m_active = true;
        }

    private:

        // Store if the script is m_active.
        bool m_active = false;

        // Store the time.
        Timer m_time;

        void CreateAnimations();

        // Object for inputs in the central light script 3.
        InputSystem *m_input = nullptr;

        // Object for the inputs from the game controller.
        GameController *m_gamecontroller = nullptr;

        // Animator for the central light script 3.
        Animator *m_animator = nullptr;

        // Object that store positions in the game.
        Vector *m_position = nullptr;

        // Not used attribute.
        int m_play = 0;

    protected:
        void ComponentUpdate() override;

};
#endif
