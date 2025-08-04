#pragma once

#include "../Core/StringHelper.h"

#include <fmod.hpp>
#include <string>
#include <map>

namespace Cpain {
	class AudioSystem {
	public:

		AudioSystem() = default;

		bool initialize();
		bool shutdown();
		void update();

		bool addSound(const std::string& filename, const std::string& name = "");
		bool playSound(const std::string& name);

	private:
		bool checkFmodResult(FMOD_RESULT result);

	private:
		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;

	};
}