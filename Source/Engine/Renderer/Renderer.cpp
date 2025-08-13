#include "Renderer.h"
#include "Texture.h"
#include <Core/Logger.h>

namespace Cpain {

    /// <summary>
    /// Initializes the renderer by setting up the SDL video subsystem.
    /// </summary>
    /// <returns>true if the SDL video subsystem was initialized successfully; false otherwise.</returns>
    bool Renderer::initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            Cpain::Logger::Error("SDL_Init Error: {}", SDL_GetError());

            return false;
        }

        if (!TTF_Init()) {
            Cpain::Logger::Error("TTF_Init Error: {}", SDL_GetError());

            return false;
        }

        return true;
    }

    /// <summary>
    /// Creates a window and associated renderer using SDL.
    /// </summary>
    /// <param name="name">The title of the window to be created.</param>
    /// <param name="width">The width of the window in pixels.</param>
    /// <param name="height">The height of the window in pixels.</param>
    /// <returns>True if the window and renderer were created successfully; false otherwise.</returns>
    bool Renderer::createWindow(const std::string& name, int width, int height, bool fullscreen) {
		m_width = width;
		m_height = height;

        m_window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
        if (m_window == nullptr) {
            Cpain::Logger::Error("SDL_CreateWindow {}", SDL_GetError());

            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            Cpain::Logger::Error("SDL_CreateRenderer {}", SDL_GetError());
 
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

        return true;
    }

    /// <summary>
    /// Updates the screen with any rendering performed since the previous call.
    /// </summary>
    void Renderer::present() {
        SDL_RenderPresent(m_renderer);
    }

    /// <summary>
    /// Sets the current drawing color for the renderer.
    /// </summary>
    /// <param name="r">The red component of the color (0-255).</param>
    /// <param name="g">The green component of the color (0-255).</param>
    /// <param name="b">The blue component of the color (0-255).</param>
    /// <param name="a">The alpha (transparency) component of the color (0-255).</param>
    void Renderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    /// <summary>
    /// Sets the current drawing color for the renderer.
    /// </summary>
    /// <param name="r">The red component of the color (0.0 to 255.0).</param>
    /// <param name="g">The green component of the color (0.0 to 255.0).</param>
    /// <param name="b">The blue component of the color (0.0 to 255.0).</param>
    /// <param name="a">The alpha (transparency) component of the color (0.0 to 255.0).</param>
    void Renderer::setColor(float r, float g, float b, float a) {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    /// <summary>
    /// Draws a line between two points using the renderer.
    /// </summary>
    /// <param name="x1">The x-coordinate of the starting point.</param>
    /// <param name="y1">The y-coordinate of the starting point.</param>
    /// <param name="x2">The x-coordinate of the ending point.</param>
    /// <param name="y2">The y-coordinate of the ending point.</param>
    void Renderer::drawLine(float x1, float y1, float x2, float y2) {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    /// <summary>
    /// Draws a point at the specified coordinates using the renderer.
    /// </summary>
    /// <param name="x">The x-coordinate of the point to draw.</param>
    /// <param name="y">The y-coordinate of the point to draw.</param>
    void Renderer::drawPoint(float x, float y) {
        SDL_RenderPoint(m_renderer, x, y);
	}

    /// <summary>
    /// Clears the current rendering target with the drawing color.
    /// </summary>
    void Renderer::clear() {
        SDL_RenderClear(m_renderer);
    }

    /// <summary>
    /// Shuts down the renderer and releases associated resources.
    /// </summary>
    void Renderer::shutdown() {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Renderer::drawTexture(Texture& texture, float x, float y) {
        vec2 size = texture.getSize();

        SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = texture.getSize().x;
        destRect.h = texture.getSize().y;

        SDL_RenderTexture(m_renderer, texture.getTexture(), NULL, &destRect);
    }

    void Renderer::drawTexture(Texture& texture, float x, float y, float angle, float scale) {
        vec2 size = texture.getSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - destRect.w * 0.5f;
        destRect.y = y - destRect.h * 0.5f;


        SDL_RenderTextureRotated(m_renderer, texture.getTexture(), NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
    }
}
