#pragma once

namespace Cpain {
	class AudioClip : public Resource{
	public:
		AudioClip() = default;
		~AudioClip() = default;

		bool load(const std::string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;

		FMOD::Sound* m_sound = nullptr;

	};
}