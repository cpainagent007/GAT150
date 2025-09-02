#include "TilemapRenderer.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"

namespace Cpain {
	FACTORY_REGISTER(TilemapRenderer)

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) {
	}

	void TilemapRenderer::start() {
		// Load the tilemap resource
		m_tilemap = resources().get<Tilemap>(m_tilemapName, getEngine().getRenderer());
		if (!m_tilemap) {
			Logger::Error("Could not load tilemap: {}", m_tilemapName);
			return;
		}
		
		// create physics bodies
		Transform transform;
		transform.scale = owner->transform.scale;
		transform.rotation = owner->transform.rotation;

		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;

		// iterate through layers
		for (auto layer : m_tilemap->getLayers()) {

			if (!layer.hasCollision) continue;

			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = m_tilemap->getTextureRect(layer, tileId);
				vec2 position = owner->transform.position + (m_tilemap->getPosition(layer, i) * owner->transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };

				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, getEngine().getPhysics());
				m_physicsBodies.push_back(std::move(physicsBody));
			}
		}
	}

	void TilemapRenderer::update(float deltaTime) {
		//
	}

	void TilemapRenderer::draw(Renderer& renderer) {
		// iterate through layers
		for (auto layer : m_tilemap->getLayers()) {
			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = m_tilemap->getTextureRect(layer, tileId);
				vec2 position = (owner->transform.position) + (m_tilemap->getPosition(layer, i) * owner->transform.scale);

				renderer.drawTexture(*layer.texture, source, position.x, position.y, owner->transform.rotation, owner->transform.scale);
			}
		}
	}

	void TilemapRenderer::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ_NAME(value, "tilemap_name", m_tilemapName);
	}
}