#pragma once

namespace Cpain {
	class RigidBody : public Component {
	public:
		vec2 velocity;
		float damping = 0.0f;

	public:
		CLASS_PROTOTYPE(RigidBody)

		void update(float deltaTime) override;

		void read(const Json::value_t& value);
	};
}