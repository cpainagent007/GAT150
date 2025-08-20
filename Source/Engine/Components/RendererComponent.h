#pragma once

#include "../Framework/Component.h"

namespace Cpain {
	class RendererComponent : public Component {
	public:
		virtual void update(float deltaTime) = 0;
		virtual void draw(class Renderer& renderer) = 0;
	};
}