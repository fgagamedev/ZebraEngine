#include "Components/Animator.hpp"

/**
    @file Animator.cpp
    @brief Manage the animations of the game.
*/

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
        if (result.first == name) {
            result.second->SetPlaying(true);
        } else {
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
    if (result == m_aMap.end()) {
        ERROR("Couldn't find animation: " << name);
    }
    result->second->SetPlaying(false);
}

/**
    @brief Provides a way to stop all animations in the map at once.
*/
void Animator::StopAllAnimations() {
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
    if (result == m_aMap.end()) {
        ERROR("Couldn't find animation: " << name);
    }
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
        if (result.first == name) {
            return result.second;
        }
    }
    return nullptr;
}
