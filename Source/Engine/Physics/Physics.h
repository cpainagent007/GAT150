#pragma once

#include <box2d/box2d.h>

namespace Cpain {
	inline b2Vec2 toB2(const vec2& v) { return b2Vec2{ v.x, v.y }; }
	inline vec2 toVec2(const b2Vec2& v) { return vec2{ v.x, v.y }; }

	class Physics {
		
	public:
		Physics() = default;

		bool initialize();
		void shutdown();
		void update(float deltaTime);

		vec2 worldToPixel(const vec2& world) {}

	private:
		b2WorldId m_worldId;
	};

}