/**
    @file Animation.cpp
    @brief Class that manages animated game behavior,
    such as game behavior and picture frames.
    @copyright LGPL. MIT License.
*/
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Components/Animation.hpp"
#include "Log/log.hpp"

/**
    @brief Responsible for instantiating the class and starting the game animation.
    @param[in] owner Points to the game initializer.
    @param[in] image Points to the image initializer.
    @param[in] playOnStart Informs whether the game has been initialized or not. false/true
*/
Animation::Animation(GameObject *owner, Image *image, bool playOnStart)
                    : Component(owner, C_DRAW) {
    if (!image) {
        ERROR("Null image not allowed");
    }
    m_image = image;
    m_isPlaying = playOnStart;
}


/**
    @brief Responsible for starting the animation. If the game is
    already running it sends to the SetPlaying method the release to start.
*/
void Animation::Start() {
    if (!m_isPlaying) {
        SetPlaying(false);
    } else {
        SetPlaying(true);
    }
}


/**
    @brief Pesponsible for sending to the Flip method of the
    Image class the information needed to instantiate the flip.
    @param[in] horizontal true/false
    @param[in] vertical true/false
*/
void Animation::SetFlip(bool horizontal, bool vertical) {
    m_image->Flip(horizontal, vertical);
}

/**
    @brief Set the animation for playing.
    @param[in] condition true/false
*/
void Animation::SetPlaying(bool condition) {
    if (m_isPlaying == condition) {
        return;
    } else {
        //nothing to do.
    }

    if (condition) {
        if (auto comp = GetOwner()->GetComponent("Renderer")) {
            comp->m_active = false;
        } else {
            //nothing to do.
        }
    } else {
        if (m_hasExitTime && m_currentFrame != m_framesQuantity - 1) {
            return;
        } else {
            if (auto comp = GetOwner()->GetComponent("Renderer")) {
                comp->m_active = true;
            } else {
                //nothing to do.
            }
        }
    }

    m_isPlaying = condition;
    m_currentFrame = 0;
}

/**
    @brief Adding frame on animation.
    @param[in] frame Points to the class responsible for creating frames.
*/
void Animation::AddFrame(Frame *frame) {
    if (!frame) {
        ERROR("Null frame pointer");
    } else {
        //nothing to do.
    }

    m_frames.push_back(frame);
    m_framesQuantity++;
}

/**
    @brief Update components if you are playing.
*/
void Animation::ComponentUpdate() {
    if (m_isPlaying) {
        DrawCurrentFrame();
        if (!m_loop && m_currentFrame == m_framesQuantity - 1) {
            SetPlaying(false);
        } else {
            //nothing to do.
        }
    } else {
        //nothing to do.
    }
}

/**
    @brief Updates the current frames on the screen.
*/
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
