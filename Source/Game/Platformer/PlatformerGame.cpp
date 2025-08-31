#include "PlatformerGame.h"

bool PlatformerGame::initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    m_scene = std::make_unique<Cpain::Scene>(this);
    m_scene->load("Scenes/prototypes.json");
    m_scene->load("Scenes/level.json");

	return true;
}

void PlatformerGame::shutdown() {
    //
}

void PlatformerGame::update(float deltaTime) {
    switch (m_gameState) {
    case GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case GameState::Title:
        m_gameState = GameState::StartGame;
        break;
    case GameState::StartGame:
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        spawnPlayer();
        spawnEnemy();
        m_gameState = GameState::Playing;
        break;
    case GameState::Playing:
        break;
    case GameState::PlayerDied:
        break;
    case GameState::EndGame:
        break;
    default:
        break;
    }

    m_scene->update(Cpain::getEngine().getTime().getDeltaTime());
}

void PlatformerGame::draw(class Cpain::Renderer& renderer) {
    m_scene->draw(renderer);
    Cpain::getEngine().getParticleSystem().draw(renderer);
}

void PlatformerGame::onPlayerDeath() {

}

void PlatformerGame::onNotify(const Cpain::Event& event) {

}

void PlatformerGame::spawnEnemy() {
    auto enemy = Cpain::instantiate("bat");
    m_scene->addActor(std::move(enemy));
}

void PlatformerGame::spawnPlayer() {
    auto player = Cpain::instantiate("platPlayer");
    m_scene->addActor(std::move(player));
}