#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <map>

#include "Music.h"
#include "SoundEffect.h"

#include "../utils/Singleton.h"
#include "../utils/checkML.h"

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

private:
	SoundManager() {}

	sdl_resource_table<SoundEffect> sfx_; // sounds map (string -> sound)
	sdl_resource_table<Music> musics_; // musics map (string -> music)
};

// SoundManager::instance()->method() --> soundManager().method()
inline SoundManager& soundManager() {
	return *SoundManager::instance();
}
