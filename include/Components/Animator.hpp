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
    AnimationMap m_aMap;
};

#endif
