#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::update(float deltaTime) {
    Cpain::Actor* player = owner->scene->getActorByName<Cpain::Actor>("platPlayer");
    if (player && m_rigidBody) {

        Cpain::vec2 direction = player->transform.position - owner->transform.position;

        if (direction.lengthSqrd() > 0.0001f) {
            direction = direction.normalized();
        }

        m_rigidBody->applyForce(direction * speed);
    }
}

void EnemyController::onCollision(class Cpain::Actor* collider) {
    auto coin = Cpain::instantiate("coin");
    coin->transform.position = owner->transform.position;
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
