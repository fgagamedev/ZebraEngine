/**
    @file UISound.cpp
    @brief Creates and plays sounds during the game.
    @copyright MIT License.
*/

#include "Components/UISound.hpp"

UISound::UISound(GameObject *owner, string message, string audio_path,
                 bool is_music, bool play_on_start)
                 : Component (owner, C_COMMON) {
    m_message = message;
    m_audio_path = audio_path;
    m_is_music = is_music;
    m_play_on_start = play_on_start;
    OnPropertyChange();
}


void UISound::Start() {}

/**
    @brief Avoids the sound to play on start while updating a component.
*/
void UISound::ComponentUpdate() {
    if (m_play_on_start) {
        Play(-1, -1);
        m_play_on_start = false;
    }
}

void UISound::FixedComponentUpdate() {}

/**
    @brief Handles what happens whenever a property changes.
    @details If the audio file is found, it plays, else, an error message is shown.
*/
void UISound::OnPropertyChange() {
    switch (m_is_music) {
        case true:
        m_music = Mix_LoadMUS(m_audio_path.c_str());
        //Verification
        if( m_music == NULL ) {
            printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
        }
        break;

        case false:
        m_sound = Mix_LoadWAV(m_audio_path.c_str());
        //Verification
        if (m_sound == NULL) {
            printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        }
        break;
    }
}

/**
    @brief If the sound consists in a music, it should play repeatedly.
    @param loops.
    @param channel.
*/
void UISound::Play(int loops, int channel) {
    if (m_is_music) {
        Mix_PlayMusic(m_music, loops);

    } else {
        Mix_PlayChannel(channel, m_sound, loops);
    }
}

/**
    @brief Stops the sound either if it's a music or not.
    @param channel.
*/
void UISound::Stop(int channel) {
    if (m_is_music) {
        Mix_HaltMusic();
    } else {
        Mix_HaltChannel(channel);
    }
}

/**
    @brief Pauses the sound either if it's a music or not.
    @param channel.
*/
void UISound::Pause(int channel) {
    if (m_is_music) {
        Mix_PauseMusic();
    }
    else {
        Mix_Pause(channel);
    }
}
