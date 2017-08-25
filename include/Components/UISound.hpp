#ifndef __UI_SOUND__
#define __UI_SOUND__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"
#include "Engine/SDLSystem.hpp"
#include "Engine/sdl2include.hpp"

#include "Log/sdl_log.hpp"

#include <string>


using namespace std;

class UISound : public Component {
public:
  UISound(GameObject *owner, string message, string audio_path, bool is_music, bool play_on_start);

  string GetComponentName() override { return "UISound"; };

  void Start() override;
  void FixedComponentUpdate() override;
  void ComponentUpdate() override;

  //-1 in loops means play forever
  //-1 in channel means chose empty channel and put sound
  void Play(int loops = -1, int channel = -1);
  void Stop(int channel = -1);
  void Pause(int channel = -1);

  inline string GetMessage(){ return m_message; };
private:
  bool m_is_music;
  string m_message;
  string m_audio_path;
  bool m_play_on_start;

  Mix_Music * m_music = nullptr;
  Mix_Chunk * m_sound = nullptr;


  void OnPropertyChange();
};

#endif
