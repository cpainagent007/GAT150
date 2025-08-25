#include "SpaceGame.h"
#include "Components/SpriteRenderer.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourceManager.h"
#include "Components/RigidBody.h"
#include "../GamePCH.h"

#include <vector>

bool SpaceGame::initialize()
{
    m_scene = std::make_unique<Cpain::Scene>(this);
    m_scene->load("scene.json");

    m_titleText = std::make_unique<Cpain::Text>(Cpain::resources().getByID<Cpain::Font>("titleFont", "QuirkyRobot.ttf", 100.0f));
    m_scoreText = std::make_unique<Cpain::Text>(Cpain::resources().getByID<Cpain::Font>("uiFont", "QuirkyRobot.ttf", 50.0f));
    m_livesText = std::make_unique<Cpain::Text>(Cpain::resources().getByID<Cpain::Font>("uiFont", "QuirkyRobot.ttf", 50.0f));

    return true;
}

void SpaceGame::update(float deltaTime)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartLevel;
        break;

    case SpaceGame::GameState::StartLevel:
    {
        m_scene->removeAll();

        auto player = Cpain::instantiate("player");
        m_scene->addActor(std::move(player));

        m_gameState = GameState::Playing;
    }
    break;
    case SpaceGame::GameState::Playing: {
        m_enemySpawnTimer -= deltaTime;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = (8 - (m_score * 0.05f));
            if (m_enemySpawnTimer < 1) m_enemySpawnTimer = 1;
            spawnEnemy();
        }

        // Player Projectile Types
        /*
         Player* player = m_scene->getActorByName<Player>("player");
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_1)) player->weapon = Player::Weapon::Rocket;
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_2)) player->weapon = Player::Weapon::Rapid;
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_3)) player->weapon = Player::Weapon::Super;
        */
       

        break;
    }
    case SpaceGame::GameState::PlayerDied:
		m_stateTimer -= deltaTime;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::EndGame;
				m_stateTimer = 2.0f;
            } else {
                m_gameState = GameState::StartLevel;
            }
        }
        break;
    case SpaceGame::GameState::EndGame:
		m_stateTimer -= deltaTime;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    float speed = 40.0f * deltaTime;
    float screenHeight = (float)Cpain::getEngine().getRenderer().getHeight();
    float screenWidth = (float)Cpain::getEngine().getRenderer().getWidth();

    m_scene->update(Cpain::getEngine().getTime().getDeltaTime());
}

void SpaceGame::draw(Cpain::Renderer& renderer) {

    m_scene->draw(renderer);

    if (m_gameState == GameState::Title) {
        m_titleText->create(renderer, "Space Game", Cpain::vec3{ 1, 1, 1 });
        m_titleText->draw(renderer, (float)(renderer.getWidth() * 0.5f) - 200.0f, 50.0f);
    }
    if (m_gameState == GameState::EndGame) {
        m_titleText->create(renderer, "Game Over", Cpain::vec3{ 1, 1, 1 });
        m_titleText->draw(renderer, (float)(renderer.getWidth() * 0.5f) - 200.0f, 50.0f);
    }

    m_scoreText->create(renderer, "Score: " + std::to_string(m_score), Cpain::vec3{ 1, 1, 1 });
    m_scoreText->draw(renderer, 10.0f, 10.0f);
    m_livesText->create(renderer, "Lives: " + std::to_string(m_lives), Cpain::vec3{ 1, 1, 1 });
    m_livesText->draw(renderer, 10.0f, 50.0f);

    Cpain::getEngine().getParticleSystem().draw(renderer);
}

void SpaceGame::onPlayerDeath() {
	m_gameState = GameState::PlayerDied;
	m_stateTimer = 2.0f;
}

void SpaceGame::shutdown() {
    //
}

void SpaceGame::spawnEnemy() {
    Cpain::Actor* player = m_scene->getActorByName<Cpain::Actor>("player");
    Cpain::vec2 position = player->transform.position + Cpain::onUnitCircle() * Cpain::getReal(200.0f, 500.0f);
    Cpain::Transform transform{ position, Cpain::getReal(0.0f, 360.0f), 0.0f };
    auto enemy = Cpain::instantiate("enemy");

    // Enemy Types
    /*
     int choice = Cpain::getInt(0, 3);
    switch (choice) {
    case 0:
        enemy->type = Enemy::Type::Basic;
        enemy->speed = (Cpain::getReal() * 400) + 300;
        enemy->fireTimer = 0;
        break;
    case 1:
        enemy->type = Enemy::Type::Fast;
        enemy->speed = (Cpain::getReal() * 800) + 600;
        enemy->fireTimer = 0;
        enemy->transform.scale = enemy->transform.scale * 0.5f;
        break;
    case 2:
        enemy->type = Enemy::Type::Shooter;
        enemy->speed = (Cpain::getReal() * 400) + 300;
        enemy->fireTimer = 5;
        break;
    case 3:
        enemy->type = Enemy::Type::Mega;
        enemy->speed = 100;
        enemy->fireTimer = 0;
        enemy->transform.scale = enemy->transform.scale * 1.2f;
        break;
    }
    */
   
    m_scene->addActor(std::move(enemy));

}