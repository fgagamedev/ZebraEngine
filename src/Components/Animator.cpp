/**
    @file Animator.cpp
    @brief Manage the animations of the game.
    @copyright MIT License.
*/
#include "Components/Animator.hpp"

/**
    @brief Animator constructor.
    @param[in] owner
    @param[in] C_DRAW Enumerator from ComponentTypes.
*/
Animator::Animator(GameObject *owner) : Component(owner, C_DRAW) {}

/**
    @brief Add a animation to a map of Animation pointers.
    @param[in] name Key of the element.
    @param[in] animation Value of the element.
*/
void Animator::AddAnimation(std::string name, Animation *animation) {
    m_aMap.emplace(name, animation);
}

/**
    @brief Search for a animation in the map to play it.
    @param[in] name Key of the targeted animation.
*/
void Animator::PlayAnimation(std::string name) {
    for (auto result : m_aMap) {
        // Checks if the first result of the variable has the same name of a given animation.
        if (result.first == name) {
            // sets the state of the animation
            result.second->SetPlaying(true);
        } else {
            // If not, set the playing state as false 
            result.second->SetPlaying(false);
        }
    }
}

/**
    @brief Search for a animation in the map to stop it.
    @param[in] name Key of the targeted animation.
*/
void Animator::StopAnimation(std::string name) {
    auto result = m_aMap.find(name);
    // If the current animations name wasnt found, show error message.
    if (result == m_aMap.end()) {
        ERROR("Couldn't find animation: " << name);
    }
    result->second->SetPlaying(false);
}

/**
    @brief Provides a way to stop all animations in the map at once.
*/
void Animator::StopAllAnimations() {
    // Sets the animations playing state as false
    for (auto result : m_aMap) {
        result.second->SetPlaying(false);
    }
}

/**
    @brief Verify if a animation of the map is playing.
    @param[in] name Key of the targeted animation.
    @return The playing status of the animation.
*/
bool Animator::IsPlaying(std::string name){
    auto result = m_aMap.find(name);

    // Searches the name of the current animation, if doesnt exist, display error message.
    if (result == m_aMap.end()) {
        ERROR("Couldn't find animation: " << name);
    }
    // If the name matches, set the playing state.
    if (result->second->IsPlaying()) {
        return true;
    }
    return false;
}

/**
    @brief Provides the pointer of an animation so that it can be used.
    @param[in] name Key of the targeted animation.
    @return pointer to an Animation.
*/
Animation *Animator::GetAnimation(std::string name) {
    for (auto result : m_aMap) {
        // If the first name of the animation was found, return the second name.
        if (result.first == name) {
            return result.second;
        }
        //If not, returns a null pointer.
    }
    return nullptr;
}
