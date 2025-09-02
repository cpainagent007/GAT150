#pragma once
#include "RendererComponent.h"

namespace Cpain {
	class TilemapRenderer : public RendererComponent {
	public:
		TilemapRenderer() = default;
		TilemapRenderer(const TilemapRenderer& other);

		CLASS_PROTOTYPE(TilemapRenderer)

		void start() override;
		void update(float deltaTime) override;
		void draw(Renderer& renderer) override;

		void read(const Json::value_t& value) override;

	private:
		std::string m_tilemapName;
		res_t<class Tilemap> m_tilemap;

		std::vector<std::unique_ptr<PhysicsBody>> m_physicsBodies;
	};
}
