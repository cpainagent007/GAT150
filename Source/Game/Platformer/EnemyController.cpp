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
    if (owner->tag != collider->tag) {

        if (m_rigidBody) {
            m_rigidBody->bodyDef.isSensor = true;
            m_rigidBody->start();
        }

        EVENT_NOTIFY(add_points, 10);
        for (int i = 0; i < 100; i++) {
            Cpain::Particle particle;
            particle.position = owner->transform.position;
            particle.velocity = Cpain::onUnitCircle() * Cpain::getReal(10.0f, 200.0f);
            particle.color = Cpain::vec3{ 1, 1, 1 };
            particle.lifetime = 2;
            Cpain::getEngine().getParticleSystem().addParticle(particle);
        }

        owner->active = false;
    }
}


void EnemyController::read(const Cpain::Json::value_t& value) {
	Object::read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
}

void EnemyController::start() {
	m_rigidBody = owner->getComponent<Cpain::RigidBody>();
}
