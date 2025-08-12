#pragma once

namespace Cpain {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius = 0.0f;

	public:

		void update(float deltaTime) override;

		bool checkCollision(ColliderComponent& other) override;

	};
}