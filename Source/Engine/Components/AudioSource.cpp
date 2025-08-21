#include "AudioSource.h"
#include "Audio/AudioClip.h"
#include "Engine.h"

namespace Cpain {
	FACTORY_REGISTER(AudioSource)

	void AudioSource::update(float deltaTime) {

	}

	void AudioSource::play() {
		auto audioClip = resources().get<AudioClip>(audioClipName, getEngine().getAudio());
		if (audioClip) {
			getEngine().getAudio().playSound(*audioClip);
		}
	}

	void AudioSource::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, audioClipName);
	}
}