#pragma once

namespace Cpain {
	class RendererComponent : public Component {
	public:
		virtual void draw(class Renderer& renderer) = 0;
	};
}