#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace Cpain{
	class Font {
	public:
		Font() = default;
		~Font();

		bool load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}