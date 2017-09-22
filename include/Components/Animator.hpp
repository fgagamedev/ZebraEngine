/**
    @file Animator.hpp
    @brief Manage the animations of the game.
    @copyright MIT License.
*/
#ifndef __ANIMATOR__
#define __ANIMATOR__

#include "Engine/Component.hpp"

#include "Components/Animation.hpp"
#include "Log/log.hpp"

#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, Animation *> AnimationMap;

class Animator : public Component {
public:
    // Responsible for declaring and creating all the game animations.
    Animator(GameObject *owner);
    void AddAnimation(std::string name, Animation *animation);
    void PlayAnimation(std::string name);
    void StopAnimation(std::string name);
    void StopAllAnimations();
    bool IsPlaying(std::string name);
    Animation *GetAnimation(std::string name);
    std::string GetComponentName() override {
        return "Animator";
    };

private:
    //local variable map animation.
    AnimationMap m_aMap;
};

#endif
