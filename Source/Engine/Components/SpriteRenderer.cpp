#include "SpriteRenderer.h"

namespace Cpain {

	void SpriteRenderer::update(float deltaTime) {

	}

	void SpriteRenderer::draw(Renderer& renderer) {
		auto texture = resources().get<Texture>(textureName, renderer).get();

		if (texture) {
			renderer.drawTexture(*texture,
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale);
		}


	}

}
