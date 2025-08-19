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

    Cpain::Json::doc_t document;
    Cpain::Json::load("scene.json", document);
    m_scene->read(document);

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

        /*

        // create player
        std::shared_ptr<Cpain::Mesh> model = std::make_shared<Cpain::Mesh>(Cpain::playerPoints, Cpain::vec3{ 0.0f, 1.0f, 0.0f });
        Cpain::Transform transform{ Cpain::vec2{ Cpain::getEngine().getRenderer().getWidth() * 0.5f, Cpain::getEngine().getRenderer().getHeight() * 0.5f }, 0, 0.2f };
        auto player = std::make_unique<Player>(transform);
        player->shipSpeed = 1000.0f;
        player->rotationSpeed = 180.0f;
        player->name = "player";
        player->tag = "player";
        player->weapon = Player::Weapon::Rocket;


        auto spriteRenderer = std::make_unique<Cpain::SpriteRenderer>();
        spriteRenderer->textureName = "Ship.png";
        player->addComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<Cpain::RigidBody>();
        rb->damping = 1.5f;
        player->addComponent(std::move(rb));

        auto collider = std::make_unique<Cpain::CircleCollider2D>();
        collider->radius = 60;
        player->addComponent(std::move(collider));

        m_scene->addActor(std::move(player));

        */

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

        Player* player = m_scene->getActorByName<Player>("player");
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_1)) player->weapon = Player::Weapon::Rocket;
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_2)) player->weapon = Player::Weapon::Rapid;
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_3)) player->weapon = Player::Weapon::Super;

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

    m_scene->draw(renderer);

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

    /*

    Player* player = m_scene->getActorByName<Player>("player");
    if (player) {
        std::shared_ptr<Cpain::Mesh> enemyModel = std::make_shared<Cpain::Mesh>(Cpain::enemyPoints, Cpain::vec3{ 1.0f, Cpain::getReal() * 0.5f, Cpain::getReal() * 0.5f });

        Cpain::vec2 position = player->transform.position + Cpain::onUnitCircle() * Cpain::getReal(500.0f, 700.0f);
        Cpain::Transform transform{ position, Cpain::getReal(0.0f, 360.0f), 0.5f};

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);
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


        auto spriteRenderer = std::make_unique<Cpain::SpriteRenderer>();
        spriteRenderer->textureName = "enemy.png";
        enemy->addComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<Cpain::RigidBody>();
        rb->damping = 0.5f;
        enemy->addComponent(std::move(rb));

        auto collider = std::make_unique<Cpain::CircleCollider2D>();
        collider->radius = 60;
        enemy->addComponent(std::move(collider));
        
        enemy->tag = "enemy";
        m_scene->addActor(std::move(enemy));

    }

    */

}