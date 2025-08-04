#include "AudioSystem.h"
#include <fmod_errors.h>
#include <iostream>

namespace Cpain {

	/// <summary>
	/// Checks if an FMOD operation was successful and prints an error message if not.
	/// </summary>
	/// <param name="result">The FMOD_RESULT value returned by an FMOD function.</param>
	/// <returns>True if the result indicates success (FMOD_OK), false otherwise.</returns>
	bool AudioSystem::checkFmodResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}

	/// <summary>
	/// Initializes the audio system using FMOD.
	/// </summary>
	/// <returns>Returns true if the audio system was successfully initialized; otherwise, returns false.</returns>
	bool AudioSystem::initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!checkFmodResult(result)) return false;

		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!checkFmodResult(result)) return false;

		return true;
	}


	bool AudioSystem::shutdown() {
		checkFmodResult(m_system->release());
		return true;
	}


	void AudioSystem::update() {
		checkFmodResult(m_system->update());
	}

	/// <summary>
	/// Adds a sound to the audio system using the specified filename and name.
	/// </summary>
	/// <param name="filename">The path to the sound file to be loaded.</param>
	/// <param name="name">The name to associate with the sound. If empty, the filename is used as the key.</param>
	/// <returns>Returns true if the sound was successfully added; returns false if a sound with the same name already exists or if loading the sound fails.</returns>
	bool AudioSystem::addSound(const std::string& filename, const std::string& name) {
		std::string key = (name.empty()) ? filename : name;
		key = toLower(key);
		if (m_sounds.find(key) != m_sounds.end()) {
			std::cerr << "Audio System: Sound with name '" << key << "' already exists." << std::endl;
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!checkFmodResult(result)) return false;

		m_sounds[key] = sound;

		return true;
	}

	/// <summary>
	/// Plays a sound by its name using the audio system.
	/// </summary>
	/// <param name="name">The name of the sound to play.</param>
	/// <returns>True if the sound was successfully played; false if the sound does not exist or playback failed.</returns>
	bool AudioSystem::playSound(const std::string& name) {
		std::string key = name;
		key = toLower(key);

		if(m_sounds.find(key) == m_sounds.end()) {
			std::cerr << "Audio System: Sound with name '" << name << "' does not exist." << std::endl;
			return false;
		}

		FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);
		if (!checkFmodResult(result)) return false;

		return true;
	}

}