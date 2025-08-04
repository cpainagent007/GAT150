#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

namespace Cpain {
	class Renderer {

	public:
		Renderer() = default;

		bool initialize();
		bool createWindow(const std::string& name, int width, int height);
		void present();

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void setColor(float r, float g, float b, float a = 1.0f);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(float x, float y);
		void clear();

		void shutdown();

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

	private:
		friend class Text;

		int m_width = 0;
		int m_height = 0;

		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

	};
}
