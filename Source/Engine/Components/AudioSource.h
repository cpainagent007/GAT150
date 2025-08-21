#pragma once
#include "Framework/Component.h"

namespace Cpain {
	class AudioSource : public Component {
	public:
		std::string audioClipName;

	public:
		CLASS_PROTOTYPE(AudioSource)

		void update(float deltaTime) override;
		void read(const Json::value_t& value);
		void play();
	};
}