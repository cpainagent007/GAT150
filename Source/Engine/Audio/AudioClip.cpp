#include "AudioClip.h"

namespace Cpain {
	AudioClip::~AudioClip() {
		if (m_sound) m_sound->release();
	}

	bool AudioClip::load(const std::string& filename, class AudioSystem& audioSystem) {
		FMOD_RESULT result = audioSystem.m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
		if (!AudioSystem::checkFmodResult(result)) return false;

		return true;
	}

}