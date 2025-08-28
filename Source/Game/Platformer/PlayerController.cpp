#include "PlayerController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::update(float deltaTime) {
	float direction = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) direction = -1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) direction = +1;

	if (direction != 0) {
		m_rigidBody->applyForce(Cpain::vec2{1, 0} * direction * speed);
	}

	if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->applyForce(Cpain::vec2{ 0, -1 } * jump);
	}
}

void PlayerController::onCollision(class Cpain::Actor* collider) {

}

void PlayerController::read(const Cpain::Json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireRate);
}

void PlayerController::start() {
	m_rigidBody = owner->getComponent<Cpain::RigidBody>();
}
