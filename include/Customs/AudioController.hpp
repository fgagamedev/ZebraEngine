#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"

#include "Customs/PlayerScript.hpp"
#include "Components/UISound.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/FirstBossAttackScript.hpp"

#include <stdlib.h>
#include <time.h>

class AudioController {
public:
  static AudioController *GetInstance();

  void StartBossFight();
  void EndBossFight();

  /*Add*/
  void AddAudio(UISound *sound);

  /*Play*/
  void PlayAudio(string name, int loops);

  /*Stop*/
  void StopAudio(string name);

  /*Pause*/
  void PauseAudio(string name);

private:
  AudioController();
  static AudioController *m_instance;

  //Objects
  std::vector<UISound *> m_sounds;



};

#endif
