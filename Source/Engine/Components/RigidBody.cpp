#include "RigidBody.h"

namespace Cpain {
	FACTORY_REGISTER(RigidBody)

	void Cpain::RigidBody::update(float deltaTime) {
		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + (damping * deltaTime)));

	}
}

