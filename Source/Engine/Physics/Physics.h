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

		static vec2 worldToPixel(const vec2& world) { return world * ms_pixelsPerUnit; }
		static vec2 pixelToWorld(const vec2& pixel) { return pixel / ms_pixelsPerUnit; }

		static void setPixelsPerUnit(float ppu) { ms_pixelsPerUnit = ppu; }

		static float ms_pixelsPerUnit;

	private:
		friend class Engine;
		void processCollisionEvents();

	private:
		friend class PhysicsBody;

		b2WorldId m_worldId;

	};

}