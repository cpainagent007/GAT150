#pragma once
#include "RendererComponent.h"

namespace Cpain {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;

	public:
		CLASS_PROTOTYPE(MeshRenderer)

		void update(float deltaTime) override;
		void draw(Renderer& renderer) override;

		void read(const Json::value_t& value);
	};
}