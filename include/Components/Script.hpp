/**
    @file Script.hpp
    @brief Class responsible for starting the game, creating an owner.
    @copyright LGPL. MIT License.
*/
#ifndef __SCRIPT__
#define __SCRIPT__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"

#include <utility>

class Script : public Component {
	public:

		// constructor and destructor
		Script(GameObject *owner);

		// pure virtual name getter
		virtual std::string GetComponentName() = 0;
};

#endif
