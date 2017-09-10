#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Components/Animation.hpp"
#include "Log/log.hpp"

Animation::Animation(GameObject *owner, Image *image, bool playOnStart)
    : Component(owner, C_DRAW) {
    if (!image) {
        ERROR("Null image not allowed");
    }
    m_image = image;
    m_isPlaying = playOnStart;
}

/**
    @brief The animation starts. Check if someone are playing and set it.
    False if there is something diferent of playing, true if playing.
*/
void Animation::Start() {
    if (!m_isPlaying) {
        SetPlaying(false);
    } else {
        SetPlaying(true);
    }
}

/**
    @brief Set the size of the image of the game based in horizontal and vertical.
    @param[in] the horizontal size.
    @param[in] the vertical size.
*/
void Animation::SetFlip(bool horizontal, bool vertical) {
    m_image->Flip(horizontal, vertical);
}

void Animation::SetPlaying(bool condition) {
    if (m_isPlaying == condition) {
        return;
    }

    if (condition) {
        if (auto comp = GetOwner()->GetComponent("Renderer")) {
            comp->active = false;
        }
    } else {
        if (m_hasExitTime && m_currentFrame != m_framesQuantity - 1) {
            return;
        } else {
            if (auto comp = GetOwner()->GetComponent("Renderer")) {
                comp->active = true;
            }
        }
    }

    m_isPlaying = condition;
    m_currentFrame = 0;
}

/**
    @brief that function is for add frame at the game. Check if there is something
    diferent of frame and ifs not, adds the frame.
    @param[in] Frame pointer that points to the current frame.
*/
void Animation::AddFrame(Frame *frame) {
    if (!frame) {
        ERROR("Null frame pointer");
    }
    m_frames.push_back(frame);
    m_framesQuantity++;
}

/**
    @brief that function is for update the componets of the Animation. Check if
    is playing and draw the current frame.
*/
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
                                                GetOwner()->GetPosition(),
                                                GetOwner()->GetWidth(),
                                                GetOwner()->GetHeight());
    } else {
        m_lastDraw = currentTicks;
        GraphicsSystem::GetInstance()->DrawFrame(m_image, GetCurrentFrame(),
                                                 GetOwner()->GetPosition(),
                                                 GetOwner()->GetWidth(),
                                                 GetOwner()->GetHeight());
        m_currentFrame = (m_currentFrame + 1) % m_framesQuantity;
    }
}

void Animation::SetLoop(bool condition) {
    m_loop = condition;
}
