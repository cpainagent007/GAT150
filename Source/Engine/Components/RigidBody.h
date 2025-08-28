#pragma once

namespace Cpain {
	class RigidBody : public Component {
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0, 0 };
		vec2 scale{ 1, 1 };

		vec2 velocity;
		float damping = 0.0f;

	public:
		RigidBody() = default;
		RigidBody(const RigidBody& other);

		CLASS_PROTOTYPE(RigidBody)

		void update(float deltaTime) override;

		void read(const Json::value_t& value);

		void start() override;

		void applyForce(const vec2& force);

		void applyTorque(float radians);

		void setVelocity(const vec2& velocity);

	private:
		std::unique_ptr<PhysicsBody> m_physicsBody;

	};
}