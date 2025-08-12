#include "RigidBody.h"

namespace Cpain {
	void Cpain::RigidBody::update(float deltaTime) {
		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + (damping * deltaTime)));

	}
}

