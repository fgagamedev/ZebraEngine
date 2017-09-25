/*
    @file Animation.hpp
    @brief Class that manages animated game behavior,
    such as game behavior and picture frames.
    @copyright LGPL. MIT License.
*/
#ifndef __ANIMATION__
#define __ANIMATION__

#include "Engine/Component.hpp"
#include "Engine/Frame.hpp"
#include "Engine/Image.hpp"
#include "Engine/sdl2include.hpp"

#include <string>
#include <vector>


class Animation : public Component {

    public:
        Animation(GameObject *owner, Image *image, bool playOnStart = false);

        inline void SetHasExitTime(bool condition) {
            m_hasExitTime = condition;
        };

        inline void SetFramesPerSecond(int frames) {
            m_framesPerSecond = frames;
        };

        inline Frame *GetCurrentFrame() {
            return m_frames[m_currentFrame];
        };

        void ComponentUpdate() override;
        void Start() override;
        void SetPlaying(bool condition);
        void SetLoop(bool condition);
        void SetFlip(bool horizontal, bool vertical);
        void AddFrame(Frame *frame);
        void DrawCurrentFrame();
        std::string GetComponentName() override {
            return "Animation";
        };

        bool IsPlaying(){
            return m_isPlaying;
        }

    private:

        // Represents the quantity of the frames of the animation.
        int m_framesQuantity = 0;

        // Represents the current frame of the animation.
        int m_currentFrame = 0;

        // Represents the frames per second of the animation.
        int m_framesPerSecond = 12;

        // Represents if someone is playing.
        bool m_isPlaying = false;

        bool m_hasExitTime = false;

        bool m_loop = false;

        // Represents the vertical flip of the animation.
        bool m_verticalFlip = false;

        // Represents the horizontal flip of the animation.
        bool m_horizontalFlip = false;
        Uint32 m_lastDraw = 0;
        std::vector<Frame *> m_frames;
        Image *m_image = nullptr;
};

#endif
