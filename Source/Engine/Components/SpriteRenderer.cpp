#include "SpriteRenderer.h"

namespace Cpain {
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::update(float deltaTime) {

	}

	void SpriteRenderer::draw(Renderer& renderer) {
		auto texture = resources().get<Texture>(textureName, renderer);

		if (texture) {
			renderer.drawTexture(*texture,
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale);
		}


	}

	void SpriteRenderer::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, textureName);
	}

}
