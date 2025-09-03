#include "PhysicsBody.h"

namespace Cpain {
	PhysicsBody::PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const class Physics& physics) {
		b2BodyDef bodyDef = b2DefaultBodyDef();

		// Set body definition
		bodyDef.type = (def.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = toB2(Physics::pixelToWorld(transform.position));
		bodyDef.rotation = b2MakeRot(degToRad(transform.rotation));
		bodyDef.motionLocks.angularZ = def.constrainAngle;
		bodyDef.gravityScale = def.gravityScale;
		bodyDef.linearDamping = def.linearDamping;
		bodyDef.angularDamping = def.angularDamping;
		bodyDef.userData = def.actor;

		// Create body
		m_bodyId = b2CreateBody(physics.m_worldId, &bodyDef);

		// Set shape definition
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.material.friction = def.friction;
		shapeDef.material.restitution = def.restitution;
		shapeDef.density = def.density;
		shapeDef.isSensor = def.isSensor;

		if (def.isSensor) shapeDef.enableSensorEvents = true;
		else shapeDef.enableContactEvents = true;

		// Create shape
		b2Vec2 hsize = toB2(Physics::pixelToWorld(size * transform.scale * 0.5f));
		switch (def.shape)
		{
		case Shape::Box:
		{
			b2Polygon box = b2MakeBox(hsize.x, hsize.y);
			b2CreatePolygonShape(m_bodyId, &shapeDef, &box);
		}
		break;
		case Shape::Capsule:
		{
			b2Capsule capsule{ b2Vec2{ 0, hsize.y - hsize.x }, b2Vec2{ 0, -(hsize.y - hsize.x) }, hsize.x };
			b2CreateCapsuleShape(m_bodyId, &shapeDef, &capsule);
		}
		break;
		case Shape::Circle:
		{
			b2Circle circle{ b2Vec2{ 0, 0 }, hsize.x };
			b2CreateCircleShape(m_bodyId, &shapeDef, &circle);
		}
		break;
		default:
			break;
		}
	}

	PhysicsBody::~PhysicsBody() {
		b2DestroyBody(m_bodyId);
	}

	vec2 PhysicsBody::getPosition() {
		return Physics::worldToPixel(toVec2(b2Body_GetPosition(m_bodyId)));
	}

	float PhysicsBody::getAngle() {
		return b2Rot_GetAngle(b2Body_GetRotation(m_bodyId));
	}

	void PhysicsBody::applyForce(const vec2& force) {
		b2Body_ApplyForceToCenter(m_bodyId, toB2(Physics::pixelToWorld(force)), true);
	}

	void PhysicsBody::applyTorque(float radians) {
		b2Body_ApplyTorque(m_bodyId, radians, true);
	}

	void PhysicsBody::setVelocity(const vec2& velocity) {
		b2Body_SetLinearVelocity(m_bodyId, toB2(Physics::pixelToWorld(velocity)));
	}

	b2BodyId PhysicsBody::getBodyId() {
		return m_bodyId;
	}
}