#include "ParticleSystem.h"
#include "Renderer.h"

namespace Cpain {

	bool ParticleSystem::initialize(int poolSize) {
		m_particles.resize(poolSize);
		
		return true;
	}

	void ParticleSystem::shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::update(float deltaTime) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifetime -= deltaTime;
				particle.active = (particle.lifetime > 0);
				particle.position += particle.velocity * deltaTime;
			}
		}
	}

	void ParticleSystem::draw(Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.setColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.drawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::addParticle(const Particle& particle) {
		Particle* pParticle = getFreeParticle();
		if (pParticle) {
			*pParticle = particle;
			pParticle->active = true;
			
		}
	}

	Particle* ParticleSystem::getFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}

		return nullptr;
	}
}