#pragma once

#include "Framework/Component.h"
#include "Renderer/TextureAnimation.h"

namespace Cpain {
	class Animator : public Component {
	public:
		struct TextureAnimInfo {
			std::string textureAnimationName;
			res_t<TextureAnimation> textureAnimation;
		};
		int frame = 0;
		float speedMultiplier{ 1 };
	public:
		CLASS_PROTOTYPE(Animator)
			void start() override;
		void update(float dt) override;
		void play(const std::string& name, bool resetFrame = true);
		void pause(bool pause) { m_paused = pause; }
		bool isPaused() const { return m_paused; }
		const std::string& getCurrentAnimationName() const { return m_currentAnimationName; }
		void read(const Json::value_t& value) override;
	private:
		float m_frameTimer = 0;
		bool m_paused = false;
		std::string m_currentAnimationName;
		TextureAnimInfo m_currentAnimation;
		std::map<std::string, TextureAnimInfo> m_animations;
		class SpriteRenderer* m_spriteRenderer{ nullptr };
	};
}