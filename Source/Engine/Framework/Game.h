#pragma once
#include <memory>

namespace Cpain {
	class Game {
	public:
		Game() = default;

		virtual bool initialize() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void shutdown() = 0;
		virtual void draw(class Renderer& renderer) = 0;

		void addPoints(int points) { m_score += points; }
		int getPoints() const { return m_score; }

		void setLives(int lives) { m_lives = lives; }
		int getLives() const { return m_lives; }

	protected:
		std::unique_ptr<class Scene> m_scene;
		int m_score = 0;
		int m_lives = 0;

	};	
}