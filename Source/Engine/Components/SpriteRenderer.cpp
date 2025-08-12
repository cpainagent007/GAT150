#include "SpriteRenderer.h"

namespace Cpain {

	void SpriteRenderer::update(float deltaTime) {

	}

	void SpriteRenderer::draw(Renderer& renderer) {
		renderer.drawTexture(resources().get<Texture>(textureName, renderer).get(),
			owner->transform.position.x,
			owner->transform.position.y,
			owner->transform.rotation,
			owner->transform.scale);
	}

}
