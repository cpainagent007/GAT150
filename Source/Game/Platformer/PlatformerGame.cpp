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
        m_gameState = GameState::Playing;
        break;
    case GameState::Playing:
        break;
    case GameState::PlayerDied:
        m_lives--;
        if (m_lives == 0) {
            EVENT_NOTIFY("player_dead");
        }
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
    if (Cpain::equalsIgnoreCase(event.id, "add_points")) {
        int points = std::get<int>(event.data);
        m_score += points;
    }
    else if (Cpain::equalsIgnoreCase(event.id, "player_dead")) {
        m_gameState = GameState::EndGame;
    }
}

void PlatformerGame::spawnEnemy() {
    Cpain::Actor* player = m_scene->getActorByName<Cpain::Actor>("player");
    Cpain::vec2 position = player->transform.position + Cpain::onUnitCircle() * Cpain::getReal(200.0f, 500.0f);
    Cpain::Transform transform{ position, Cpain::getReal(0.0f, 360.0f), 0.2f };
    auto enemy = Cpain::instantiate("bat", transform);
    m_scene->addActor(std::move(enemy));
}

void PlatformerGame::spawnPlayer() {
    auto player = Cpain::instantiate("platPlayer");
    m_scene->addActor(std::move(player));
}