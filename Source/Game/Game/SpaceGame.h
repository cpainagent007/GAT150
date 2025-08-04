#pragma once

#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public Cpain::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartLevel,
		Playing,
		PlayerDied,
		EndGame
	};

public:
	SpaceGame() = default;

	bool initialize() override;
	void update(float deltaTime) override;
	void shutdown() override;
	void draw(class Cpain::Renderer& renderer) override;

	void onPlayerDeath();

private:

	void spawnEnemy();

private:
	std::unique_ptr<Cpain::Scene> m_scene;
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	std::shared_ptr<class Cpain::Font> m_titleFont;
	std::shared_ptr<class Cpain::Font> m_uiFont;

	std::unique_ptr<class Cpain::Text> m_titleText;
	std::unique_ptr<class Cpain::Text> m_scoreText;
	std::unique_ptr<class Cpain::Text> m_livesText;
};