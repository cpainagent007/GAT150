#pragma once

#include <box2d/box2d.h>

namespace Cpain {
	class PhysicsBody {
	public:
		enum class Shape {
			Box,
			Circle,
			Capsule
		};
	
		struct PhysicsBodyDef {
			// Body
			float gravityScale = 1;
			float linearDamping = 0.2f;
			float angularDamping = 0.2f;
			bool  constrainAngle = false;
			bool  isDynamic = true;

			// Material
			float friction = 0.3f;
			float restitution = 0.5f;
			float density = 1.0f;

			// Shape
			Shape shape = Shape::Box;
			bool isSensor = false;

			class Actor* actor{ nullptr };
		};

	public:
		PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const class Physics& physics);
		~PhysicsBody();

		vec2 getPosition();
		float getAngle();

		void applyForce(const vec2& force);
		void applyTorque(float radians);
		void setVelocity(const vec2& velocity);
		b2BodyId getBodyId();

	private:
		b2BodyId m_bodyId = b2_nullBodyId;

	};
}