#include "SpriteRenderer.h"
#include <Engine.h>

namespace Cpain {
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::update(float deltaTime) {
		
	}

	void SpriteRenderer::draw(Renderer& renderer) {
		if (texture) {
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.drawTexture(*texture,
					textureRect,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
			else {
				renderer.drawTexture(*texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
		}
	}

	void SpriteRenderer::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, textureName);
	}

	void SpriteRenderer::start() {
		if (!texture && !textureName.empty()) {
			texture = resources().get<Texture>(textureName, getEngine().getRenderer());
		}
	}

}
