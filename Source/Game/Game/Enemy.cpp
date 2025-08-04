#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Bullet.h"
#include "GameData.h" 
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Player.h"
#include "Math/Vector2.h"

void Enemy::update(float deltaTime) {

	bool playerVisible = false;
	
	Player* player = scene->getActorByName<Player>("player");
	if (player) {
		Cpain::vec2 direction{ 1, 0 };
		direction = player->transform.position - transform.position;

		direction = direction.normalized();
		Cpain::vec2 forward = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(transform.rotation));

		float angle = Cpain::radToDeg(Cpain::vec2::angleBetween(forward, direction));
		playerVisible = (angle < 30);

		if (playerVisible) {
			float angle = Cpain::vec2::signedAngleBetween(forward, direction);
			angle = Cpain::sign(angle);
			transform.rotation += Cpain::radToDeg((angle * 3) * deltaTime);
		}
	}

	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(transform.rotation)) * speed;
	velocity += force * deltaTime;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	switch (type) {
	case Type::Basic:
		break;
	case Type::Fast:
		break;
	case Type::Shooter:
		fireTimer -= deltaTime;
		if (fireTimer <= 0 && playerVisible) {
			fireTimer = fireRate;

			std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(Cpain::bulletPoints, Cpain::vec3{ 1.0f, 0.0f, 0.0f });
			Cpain::Transform transform{ this->transform.position, this->transform.rotation, 5 };
			auto bullet = std::make_unique<Bullet>(transform, model);
			bullet->speed = 3.0f;
			bullet->lifespan = 1.0f;
			bullet->name = "bullet";
			bullet->tag = "enemy";

			scene->addActor(std::move(bullet));

		}
		break;
	case Type::Mega:
		break;
	}
	

	Actor::update(deltaTime);
}

void Enemy::onCollision(Actor* collider){
	if (tag != collider->tag) {
		active = false;
		scene->getGame()->addPoints(10);
		for (int i = 0; i < 100; i++) {
			Cpain::Particle particle;
			particle.position = transform.position;
			particle.velocity = Cpain::onUnitCircle() * Cpain::getReal(10.0f, 200.0f);
			particle.color = Cpain::vec3{ 1.0f, Cpain::getReal(0.5f, 0.9f), 0.0f };
			particle.lifetime = 2;
			Cpain::getEngine().getParticleSystem().addParticle(particle);
	
		}
	}
}
