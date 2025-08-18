#include "MeshRenderer.h"



namespace Cpain {
	FACTORY_REGISTER(MeshRenderer)

	void MeshRenderer::update(float deltaTime) {

	}

	void MeshRenderer::draw(Renderer& renderer) {
		auto mesh = resources().get<Mesh>(meshName);
		if (mesh) {
			mesh->draw(renderer, owner->transform);
		}
	}
}