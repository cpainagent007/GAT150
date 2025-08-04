#pragma once

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

#include <vector>

namespace Cpain {
	struct Particle {
		bool active = false;
		float lifetime = 1;

		vec2 position;
		vec2 velocity;
		vec3 color;
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool initialize(int poolSize = 1000);
		void shutdown();

		void update(float deltaTime);
		void draw(class Renderer& renderer);

		void addParticle(const Particle& particle);

	private:
		Particle* getFreeParticle();

	private:
		std::vector<Particle> m_particles;

	};
}