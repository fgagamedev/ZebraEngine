#include "Components/Animation.h"
#include "Engine/GameObject.h"
#include "Engine/GraphicsSystem.h"
#include "Log/log.h"

Animation::Animation(GameObject *owner, Image *image, bool playOnStart)
    : Component(owner, C_DRAW) {
  if (!image)
    ERROR("Null image not allowed");
  m_image = image;
  m_isPlaying = playOnStart;
}

void Animation::Start() {
  if (!m_isPlaying)
    SetPlaying(false);
  else
    SetPlaying(true);
}

void Animation::SetFlip(bool horizontal, bool vertical) {
  m_image->Flip(horizontal, vertical);
}

void Animation::SetPlaying(bool condition) {
  if (m_isPlaying == condition)
    return;

  if (condition) {
    if (auto comp = GetOwner()->GetComponent("Renderer"))
      comp->active = false;
  } else {
    if (m_hasExitTime && m_currentFrame != m_framesQuantity - 1) {
      return;
    } else {
      if (auto comp = GetOwner()->GetComponent("Renderer"))
        comp->active = true;
    }
  }

  m_isPlaying = condition;
  m_currentFrame = 0;
}

void Animation::AddFrame(Frame *frame) {
  if (!frame)
    ERROR("Null frame pointer");
  m_frames.push_back(frame);
  m_framesQuantity++;
}

void Animation::ComponentUpdate() {
  if (m_isPlaying) {
    DrawCurrentFrame();
    if (!m_loop && m_currentFrame == m_framesQuantity - 1) {
      SetPlaying(false);
    }
  }
}

void Animation::DrawCurrentFrame() {
  Uint32 currentTicks = SDL_GetTicks();
  if (currentTicks - m_lastDraw < (Uint32)(1000 / m_framesPerSecond)) {
    GraphicsSystem::GetInstance()->DrawFrame(m_image, GetCurrentFrame(),
                                             GetOwner()->GetPosition());
  } else {
    m_lastDraw = currentTicks;
    GraphicsSystem::GetInstance()->DrawFrame(m_image, GetCurrentFrame(),
                                             GetOwner()->GetPosition());
    m_currentFrame = (m_currentFrame + 1) % m_framesQuantity;
  }
}

void Animation::SetLoop(bool condition) { m_loop = condition; }