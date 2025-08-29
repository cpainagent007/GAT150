#include "RigidBody.h"
#include "../Engine.h"
#include "../Math/Vector2.h"

namespace Cpain {
	RigidBody::RigidBody(const RigidBody& other) {
		bodyDef = other.bodyDef;
		size = other.size;

		if (other.m_physicsBody) {
			m_physicsBody = std::make_unique<PhysicsBody>(*other.m_physicsBody);
		}
	}

	void RigidBody::applyForce(const vec2& force) {
		m_physicsBody->applyForce(force);
	}

	void RigidBody::applyTorque(float radians) {
		m_physicsBody->applyTorque(radians);
	}

	FACTORY_REGISTER(RigidBody)

	void RigidBody::update(float deltaTime) {
		owner->transform.position = m_physicsBody->getPosition();
		owner->transform.rotation = radToDeg(m_physicsBody->getAngle());

	}

	void RigidBody::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, size);
		JSON_READ(value, scale);

		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (equalsIgnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (equalsIgnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (equalsIgnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}

	void RigidBody::start() {
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0) {
			auto spriteRenderer = owner->getComponent<SpriteRenderer>();
			if (spriteRenderer) {
				size = spriteRenderer->texture->getSize();
			}
		}
		auto scaledSize = vec2{ size.x * scale.x, size.y * scale.y };
		m_physicsBody = std::make_unique<PhysicsBody>(owner->transform, scaledSize, bodyDef, getEngine().getPhysics());
	}

	void RigidBody::setVelocity(const vec2& velocity) {
		m_physicsBody->setVelocity(velocity);
	}
}

