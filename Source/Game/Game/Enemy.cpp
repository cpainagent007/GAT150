#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Bullet.h"
#include "GameData.h" 
#include "Math/Vector3.h"
#include "Renderer/Mesh.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Player.h"
#include "Math/Vector2.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Enemy)

void Enemy::update(float deltaTime) {

	bool playerVisible = false;
	
	Cpain::Actor* player = owner->scene->getActorByName<Cpain::Actor>("player");
	if (player) {
		Cpain::vec2 direction{ 1, 0 };
		direction = player->transform.position - owner->transform.position;

		direction = direction.normalized();
		Cpain::vec2 forward = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(owner->transform.rotation));

		float angle = Cpain::radToDeg(Cpain::vec2::angleBetween(forward, direction));
		playerVisible = (angle < 30);

		if (playerVisible) {
			float angle = Cpain::vec2::signedAngleBetween(forward, direction);
			angle = Cpain::sign(angle);
			m_rigidBody->applyTorque(angle * 5);

		}
	}

	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(owner->transform.rotation)) * speed;

	if (m_rigidBody) {
		m_rigidBody->applyForce(force);
	}
	

	owner->transform.position.x = Cpain::wrap(owner->transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	owner->transform.position.y = Cpain::wrap(owner->transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	// Enemy Type Behavior
	/*
	switch (type) {
	case Type::Basic:
		break;
	case Type::Fast:
		break;
	case Type::Shooter:
	*/
		fireTimer -= deltaTime;
		if (fireTimer <= 0 && playerVisible) {
			fireTimer = fireRate;

			Cpain::Transform transform{ owner->transform.position, owner->transform.rotation, 0.2f };
			auto bullet = std::make_unique<Cpain::Actor>(transform);
			bullet->lifespan = 1.0f;
			bullet->name = "bullet";
			bullet->tag = "enemy";

			auto spriteRenderer = std::make_unique<Cpain::SpriteRenderer>();
			spriteRenderer->textureName = "EnemyRocket.png";

			bullet->addComponent(std::move(spriteRenderer));

			auto rb = std::make_unique<Cpain::RigidBody>();
			bullet->addComponent(std::move(rb));

			auto collider = std::make_unique<Cpain::CircleCollider2D>();
			collider->radius = 30;
			bullet->addComponent(std::move(collider));

			owner->scene->addActor(std::move(bullet));
			
		}
		/*
		break;
	case Type::Mega:
		break;
	}
	*/

}

void Enemy::onCollision(Cpain::Actor* collider){
	if (owner->tag != collider->tag) {
		owner->active = false;
		EVENT_NOTIFY(add_points, 10);
		for (int i = 0; i < 100; i++) {
			Cpain::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = Cpain::onUnitCircle() * Cpain::getReal(10.0f, 200.0f);
			particle.color = Cpain::vec3{ 1.0f, Cpain::getReal(0.5f, 0.9f), 0.0f };
			particle.lifetime = 2;
			Cpain::getEngine().getParticleSystem().addParticle(particle);
	
		}
	}
}

void Enemy::start(){
	OBSERVER_ADD(player_dead);
	m_rigidBody = owner->getComponent<Cpain::RigidBody>();
	fireTimer = fireRate;
}

void Enemy::onNotify(const Cpain::Event& event) {
	if (Cpain::equalsIgnoreCase(event.id, "player_dead")) {
		owner->active = false;
	}
}
