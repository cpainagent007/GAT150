#pragma once

#include "Object.h"

namespace Cpain {
	class Component : public Object {
	public:
		class Actor* owner = nullptr;

	public:
		Component() = default;

		virtual void update(float deltaTime) = 0;
		virtual void start(){}
		virtual void destroyed(){}
	};
}