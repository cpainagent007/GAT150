#include "Actor.h"

namespace Cpain {
		
	void Actor::update(float deltaTime) {
		if (!active) return;

		if (lifespan != 0) {
			lifespan -= deltaTime;
			active = (lifespan > 0);
		}

		transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + (damping * deltaTime)));
	}

	void Actor::draw(Renderer& renderer) {
		if (!active) return;

		m_model->draw(renderer, transform);
	}

	float Actor::getRadius() {
		return (m_model) ? m_model->getRadius() * (transform.scale * 0.9f) : 0.0f;
	}

}
