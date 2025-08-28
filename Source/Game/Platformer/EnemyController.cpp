#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::update(float deltaTime) {
	float direction = 0;

	Cpain::Actor* player = owner->scene->getActorByName<Cpain::Actor>("platPlayer");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) direction = -1;
		else direction = +1;
	}

	if (direction != 0) {
		m_rigidBody->applyForce(Cpain::vec2{ 1, 0 } *direction * speed);
	}

	if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->applyForce(Cpain::vec2{ 0, -1 } *jump);
	}
}

void EnemyController::onCollision(class Cpain::Actor* collider) {

}

void EnemyController::read(const Cpain::Json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireRate);
}

void EnemyController::start() {
	m_rigidBody = owner->getComponent<Cpain::RigidBody>();
}
