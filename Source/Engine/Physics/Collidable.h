#pragma once

namespace Cpain {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void onCollision(class Actor* other) = 0;
	};
}