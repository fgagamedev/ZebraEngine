#ifndef __ANIMATION__
#define __ANIMATION__

#include "Engine/Component.hpp"
#include "Engine/Frame.hpp"
#include "Engine/Image.hpp"
#include "Engine/sdl2include.hpp"

#include <string>
#include <vector>

/**
    @file Animation.hpp
    @brief Class that represents the entire game and manages the main screens.
    @copyright LGPL. MIT License.
*/

class Animation : public Component {
public:
  Animation(GameObject *owner, Image *image, bool playOnStart = false);
  inline void SetHasExitTime(bool condition) { m_hasExitTime = condition; };
  inline void SetFramesPerSecond(int frames) { m_framesPerSecond = frames; };
  inline Frame *GetCurrentFrame() { return m_frames[m_currentFrame]; };
  void ComponentUpdate() override;
  void Start() override;
  void SetPlaying(bool condition);
  void SetLoop(bool condition);
  void SetFlip(bool horizontal, bool vertical);
  void AddFrame(Frame *frame);
  void DrawCurrentFrame();
  std::string GetComponentName() override { return "Animation"; };
  bool IsPlaying(){return m_isPlaying;}
private:
  int m_framesQuantity = 0;
  int m_currentFrame = 0;
  int m_framesPerSecond = 12;
  bool m_isPlaying = false;
  bool m_hasExitTime = false;
  bool m_loop = false;
  bool m_verticalFlip = false;
  bool m_horizontalFlip = false;
  Uint32 m_lastDraw = 0;
  std::vector<Frame *> m_frames;
  Image *m_image = nullptr;
};

#endif // __ANIMATION__
