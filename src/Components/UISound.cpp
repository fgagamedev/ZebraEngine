#include "Components/UISound.hpp"

UISound::UISound(GameObject *owner, string message, string audio_path, bool is_music, bool play_on_start)

	: Component(owner, C_COMMON) {

		m_message = message;
		m_audio_path = audio_path;
		m_is_music = is_music;
		m_play_on_start = play_on_start;
		OnPropertyChange();
}


void UISound::Start() {}

void UISound::ComponentUpdate() {
  	if(m_play_on_start){
        Play(-1, -1);
        m_play_on_start = false;
    }
}

void UISound::FixedComponentUpdate() {}

void UISound::OnPropertyChange() {
 
  	switch (m_is_music) {
	case true:
		m_music = Mix_LoadMUS(m_audio_path.c_str());
		//Verification
		if( m_music == NULL ) {
	   		printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
	    	//success = false;
		} 
	break;

	case false:
		m_sound = Mix_LoadWAV(m_audio_path.c_str());
		//Verification
		if(m_sound == NULL){
		printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		//success = false;
	}
	break;
	}
}

void UISound::Play(int loops, int channel) {
    if(m_is_music){
		Mix_PlayMusic(m_music, loops);
        
    } else{
         Mix_PlayChannel(channel, m_sound, loops);
    }
}

void UISound::Stop(int channel){
    if(m_is_music) Mix_HaltMusic();
    else Mix_HaltChannel(channel);
}

void UISound::Pause(int channel){
    if(m_is_music) Mix_PauseMusic();
    else Mix_Pause(channel);
}

 //Free the music
    //Mix_FreeMusic( gMusic );
    //gMusic = NULL;
