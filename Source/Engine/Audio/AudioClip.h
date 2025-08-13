#pragma once

#include "Resources/Resource.h"

namespace Cpain {
	class AudioClip : public Resource{
	public:
		AudioClip() = default;
		~AudioClip();

		bool load(const std::string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;

		FMOD::Sound* m_sound = nullptr;

	};
}