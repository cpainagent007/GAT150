#pragma once
#include "Renderer.h"
#include "Font.h"
#include "../Math/Vector3.h"

#include <memory>

namespace Cpain {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<class Font> font) : m_font{ font } {}
		~Text();

		bool create(class Renderer& renderer, const std::string& text, const vec3& color);
		void draw(class Renderer& renderer, float x, float y);

	private:
		std::shared_ptr<class Font> m_font = nullptr;
		SDL_Texture* m_texture{ nullptr };
	};
}