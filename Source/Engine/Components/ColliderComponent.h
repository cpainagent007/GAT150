#pragma once

namespace Cpain {
	class ColliderComponent : public Component {
	public:
		virtual bool checkCollision(ColliderComponent& other) = 0;
	};
}