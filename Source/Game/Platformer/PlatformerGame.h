#pragma once

#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Event/Observer.h"
#include "../GamePCH.h"

class PlatformerGame : public Cpain::Game, public Cpain::IObserver {
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

	float spawnTimeMin = 1.0f;
	float spawnTime = 5.0f;
	float timer = 0.0f;

public:
	PlatformerGame() = default;

	bool initialize() override;
	void update(float deltaTime) override;
	void shutdown() override;
	void draw(class Cpain::Renderer& renderer) override;

	void onPlayerDeath();

	void onNotify(const Cpain::Event& event);

private:

	void spawnEnemy();
	void spawnPlayer();

private:
	std::unique_ptr<Cpain::Scene> m_scene;
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	std::unique_ptr<class Cpain::Text> m_titleText;
	std::unique_ptr<class Cpain::Text> m_scoreText;
	std::unique_ptr<class Cpain::Text> m_livesText;
};