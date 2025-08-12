#pragma once

namespace Cpain {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		void update(float deltaTime) override;
		void draw(Renderer& renderer) override;

	};
}