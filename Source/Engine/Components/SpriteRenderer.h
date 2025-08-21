#pragma once

namespace Cpain {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void update(float deltaTime) override;
		void draw(Renderer& renderer) override;

		void read(const Json::value_t& value);

	};
}