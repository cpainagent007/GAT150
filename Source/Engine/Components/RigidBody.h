#pragma once

namespace Cpain {
	class RigidBody : public Component {
	public:
		vec2 velocity;
		float damping = 0.0f;

	public:
		void update(float deltaTime) override;
	};
}