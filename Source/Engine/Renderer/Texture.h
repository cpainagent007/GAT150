#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "../Math/Vector2.h"

namespace Cpain {

    class Renderer;

    class Texture {
    public:
        ~Texture();

        bool load(const std::string& filename, Renderer& renderer);
        vec2 getSize();

        SDL_Texture* getTexture() {
            return m_texture;
        }

    private:
        SDL_Texture* m_texture = nullptr;
    };

}
