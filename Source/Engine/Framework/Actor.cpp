#include "Actor.h"
#include "../Renderer/Renderer.h"

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

		renderer.drawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	float Actor::getRadius() {
		return (m_texture) ? (m_texture->getSize().length() * 0.5) * (transform.scale * 0.9f) : 0.0f;
	}

}
