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
        timer = spawnTime;
        m_gameState = GameState::Title;
        break;
    case GameState::Title:
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) m_gameState = GameState::StartGame;
        break;
    case GameState::StartGame:
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        spawnPlayer();
        m_gameState = GameState::Playing;
        break;
    case GameState::Playing:
        if (timer <= 0.0f) {
            spawnEnemy();
            timer = spawnTime - (m_score/10);
            if (timer <= spawnTimeMin) timer = spawnTimeMin;
        }
        timer -= deltaTime;
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
    
    int screenWidth = Cpain::getEngine().getRenderer().getWidth();
    int screenHeight = Cpain::getEngine().getRenderer().getHeight();
    Cpain::vec2 position;

    int side = Cpain::getInt(0, 2);

    switch (side) {
    case 0:
        position = Cpain::vec2{ Cpain::getReal(0.0f, (float)screenWidth), 0 };
        break;
    case 1:
        position = Cpain::vec2{ -10.0f, Cpain::getReal(0.0f, (float)screenHeight/2)};
        break;
    case 2:
        position = Cpain::vec2{ ((float)screenWidth + 10.0f), Cpain::getReal(0.0f, (float)screenHeight/2)};
        break;
    }


    auto enemy = Cpain::instantiate("bat", position);
    m_scene->addActor(std::move(enemy));
    
}

void PlatformerGame::spawnPlayer() {
    auto player = Cpain::instantiate("platPlayer");
    m_scene->addActor(std::move(player));
}