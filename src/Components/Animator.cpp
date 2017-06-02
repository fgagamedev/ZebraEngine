#include "Components/Animator.h"

Animator::Animator(GameObject *owner) : Component(owner, C_DRAW) {}

void Animator::AddAnimation(std::string name, Animation *animation) {
  m_aMap.emplace(name, animation);
}

void Animator::PlayAnimation(std::string name) {
  for (auto result : m_aMap) {
    if (result.first == name)
      result.second->SetPlaying(true);
    else
      result.second->SetPlaying(false);
  }
}

void Animator::StopAnimation(std::string name) {
  auto result = m_aMap.find(name);
  if (result == m_aMap.end())
    ERROR("Couldn't find animation: " << name);
  result->second->SetPlaying(false);
}

void Animator::StopAllAnimations() {
  for (auto result : m_aMap)
    result.second->SetPlaying(false);
}

Animation *Animator::GetAnimation(std::string name) {
  for (auto result : m_aMap)
    if (result.first == name)
      return result.second;
  return nullptr;
}
