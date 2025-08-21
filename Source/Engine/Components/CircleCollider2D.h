#pragma once

namespace Cpain {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius = 0.0f;

	public:
		CLASS_PROTOTYPE(CircleCollider2D)

		void update(float deltaTime) override;

		bool checkCollision(ColliderComponent& other) override;

		void read(const Json::value_t& value);

	};
}