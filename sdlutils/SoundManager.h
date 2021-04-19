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
		musics_.clear();
		sfx_.clear();
	}

	void addMusic(std::string key, std::string path) {
		musics_.emplace(key, path);
	}

	void addSFX(std::string key, std::string path) {
		sfx_.emplace(key, path);
	}

	void playMusic(std::string key) {
		if (&musics_.at(key) != currentMusic) {
			currentMusic->pauseMusic();
			currentMusic = &musics_.at(key);
			currentMusic->play();
		}
	}

	void playSFX(std::string key) {
		if (&sfx_.at(key) != currentSFX) {
			currentSFX->pauseChannel();
			currentSFX = &sfx_.at(key);
			currentSFX->play();
		}
	}

	void stopCurrentMusic() {
		if (currentMusic != nullptr)
			currentMusic->haltMusic();
	}

	void pauseCurrentMusic() {
		if (currentMusic != nullptr)
			currentMusic->pauseMusic();
	}

	void resumeCurrentMusic() {
		if (currentMusic != nullptr)
			currentMusic->resumeMusic();
	}

	float getMusicVolume() { return musicVolume; }

	float getSFXVolume() { return sfxVolume; }

	void setMusicVolume(float musV) {
		musicVolume = musV;
		// aqui va el bucle que setea el volumen por cada cancion
		/*for(int i = 0; i < musics_.size(); ++i)
			musics_[i]*/
	}

	void setSFXVolume(float sfxV) {
		sfxVolume = sfxV;
		// aqui va el bucle que setea el volumen por cada sonido
		/*for(int i = 0; i < sfx_.size(); ++i)
			sfx_[i]*/
	}

private:
	SoundManager() {}

	sdl_resource_table<SoundEffect> sfx_; // sounds map (string -> sound)
	sdl_resource_table<Music> musics_; // musics map (string -> music)

	Music* currentMusic = nullptr;
	SoundEffect* currentSFX = nullptr;

	float musicVolume = 0, sfxVolume = 0;
};

// SoundManager::instance()->method() --> soundManager().method()
inline SoundManager& soundManager() {
	return *SoundManager::instance();
}
