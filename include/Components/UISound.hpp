/**
    @file UISound.hpp
    @brief Creates and plays sounds during the game.
    @copyright MIT License.
*/

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
    UISound(GameObject *owner, string message, string audio_path, bool is_music,
            bool play_on_start);

    string GetComponentName() override {
        return "UISound";
    };

    void Start() override;
    void FixedComponentUpdate() override;
    void ComponentUpdate() override;

    void Play(int loops = playForever, int channel = emptyChannel);
    void Stop(int channel = emptyChannel);
    void Pause(int channel = emptyChannel);

    inline string GetMessage(){
        return m_message;
    };

private:
    // Store if the music is playing.
    bool m_isMusic;
    // Store a message.
    string m_message;
    // Store the path to the audio file
    string m_audioPath;
    // Store if the sound should play in the start.
    bool m_playOnStart;

    // Store the music object.
    Mix_Music *m_music = nullptr;
    // Store the sound effect object.
    Mix_Chunk *m_sound = nullptr;

    void OnPropertyChange();
    // Means that the play loop has no end.
    static const int playForever = -1;
    // Means chose empty channel.
    static const int emptyChannel = -1;
};

#endif
