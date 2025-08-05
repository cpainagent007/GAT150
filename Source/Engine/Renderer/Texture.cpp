#include "Texture.h"
#include "Renderer.h"
#include "../Math/Vector2.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


    Cpain::Texture::~Texture()
    {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }

    bool Cpain::Texture::load(const std::string& filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer.getSDLRenderer(), surface);

        SDL_DestroySurface(surface);

        if (m_texture == nullptr)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }


    Cpain::vec2 Cpain::Texture::getSize()
    {
        float width = 0;
        float height = 0;

        SDL_GetTextureSize(m_texture, &width, &height);

        return Vector2{ static_cast<float>(width), static_cast<float>(height) };
    }

