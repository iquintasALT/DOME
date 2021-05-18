#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <map>

#include "Music.h"
#include "SoundEffect.h"

#include "../utils/Singleton.h"
#include "../utils/checkML.h"

enum class MusicState { PLAYING, PAUSED, LOOPED };

class SoundManager : public Singleton<SoundManager> {

	friend Singleton<SoundManager>;

public:
	template<typename T>
	using sdl_resource_table = std::map<std::string, T>;

	virtual ~SoundManager() {
		stopCurrentMusic();
		musics_.clear();
		sfx_.clear();

		Mix_Quit(); // quit SDL_mixer
	}

	void initMixer() {
		// initialize SDL_Mixer
		int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		assert(mixOpenAudio == 0);
		int mixInit_ret = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
		assert(mixInit_ret != 0);
		SoundEffect::setNumberofChannels(8); // we start with 8 channels
	}

	void addMusic(std::string key, std::string path) {
		musics_.emplace(key, path);
	}

	void addSFX(std::string key, std::string path, int volume) {
		sfx_.emplace(key, path);
		sfx_.at(key).setVolume(volume);
	}

	void playMusic(std::string key) {
		if (&musics_.at(key) != currentMusic) {
			stopCurrentMusic();
			currentMusic = &musics_.at(key);
			currentMusic->play();
		}
	}

	void playSFX(std::string key) {
		sfx_.at(key).play();
	}

	//ESTO LO PARA Y LO QUITA
	void stopCurrentMusic() { 
		if (currentMusic != nullptr) {
			currentMusic->haltMusic();
			currentMusic = nullptr;
		}
	}

	//ESTO LO PAUSA Y SE PUEDE REANUDAR
	void pauseCurrentMusic() {
		if (currentMusic != nullptr)
			currentMusic->pauseMusic();
	}

	void resumeCurrentMusic() {
		if (currentMusic != nullptr)
			currentMusic->resumeMusic();
	}

	void changeSongWithFade(std::string key, int ticks) {
		// this works, but weneed a way to get the damn end of the fade out so rn it does not work properly but w.e.
		// currentMusic->fadeOut(ticks);

		playMusic(key);
	}

	float getMusicVolume() { return musicVolume; }

	float getSFXVolume() { return sfxVolume; }

	float getMaxVolume() { return maxVolume; }

	float getMaxSfxVolume() { return maxSfxVolume; }

	void setMusicVolume(float musV) {
		musicVolume = musV;
		for (sdl_resource_table<Music>::iterator it = musics_.begin();
			it != musics_.end(); ++it) {
			(*it).second.setMusicVolume(musicVolume);
		}
	}

	void setSFXVolume(float sfxV) {
		sfxVolume = sfxV;
		SoundEffect::setChannelVolume(sfxVolume);
	}

private:
	SoundManager() {}

	sdl_resource_table<SoundEffect> sfx_; // sounds map (string -> sound)
	sdl_resource_table<Music> musics_; // musics map (string -> music)

	Music* currentMusic = nullptr;

	float musicVolume = 40, sfxVolume = 40, maxVolume = 80, maxSfxVolume = 80;
};

// SoundManager::instance()->method() --> soundManager().method()
inline SoundManager& soundManager() {
	return *SoundManager::instance();
}
