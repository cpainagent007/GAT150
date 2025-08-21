#include "RigidBody.h"

namespace Cpain {
	FACTORY_REGISTER(RigidBody)

	void RigidBody::update(float deltaTime) {
		owner->transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + (damping * deltaTime)));

	}

	void RigidBody::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, damping);
		JSON_READ(value, velocity);
	}
}

