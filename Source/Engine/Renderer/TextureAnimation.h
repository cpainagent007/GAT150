#pragma once

namespace Cpain {
	class Texture;
	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;
		~TextureAnimation() = default;
		bool load(const std::string& filename, class Renderer& renderer);
		vec2 getSize() const;
		rect getFrameRect(int frame) const;
		int getTotalFrames() const { return m_totalFrames; }
		float getFPS() const { return m_framesPerSecond; }
		bool isValidFrame(int frame) const { return frame >= 0 && frame < m_totalFrames; }
		bool isLooping() const { return m_loop; }
		res_t<Texture> getTexture() { return m_texture; }
	private:
		int m_columns = 0;
		int m_rows = 0;
		int m_startFrame = 0;
		int m_totalFrames = 0;
		float m_framesPerSecond = 0;
		bool m_loop = true;
		res_t<Texture> m_texture;
	};
}