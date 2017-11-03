/**
    @file TopCenterLightScript.hpp
    @brief This class contains all attributes and methods that manages the central light in the game.
    @copyright LGPL. MIT License.
*/
#ifndef __TOP_CENTER_LIGHT_SCRIPT__
#define __TOP_CENTER_LIGHT_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"

#include "Math/Vector.hpp"

#include <string>

class TopCenterLightScript : public Script {

	public:
		TopCenterLightScript(GameObject *owner);
		std::string GetComponentName() override {
			return "TopCenterLightScript";
		};

		void FixedComponentUpdate() override;
		void Start() override;

        // Represents if this is script is activeted or not.
		void Activate() {
			active = true;
		}


	private:

        // Represents if this is script is activeted or not.
		bool active = false;

        // Instantiating time system.
		Timer time;

		void CreateAnimations();

        // Instantiating input system of the keyboard.
		InputSystem *m_input = nullptr;

        // Instantiating joystick.
		GameController *m_gameController = nullptr;

        // Instantiating animations.
		Animator *m_animator = nullptr;

        // Instantiating vector.
		Vector *m_position = nullptr;

        // State of the script.
		int play = 0;

	protected:
		void ComponentUpdate() override;

};
#endif
