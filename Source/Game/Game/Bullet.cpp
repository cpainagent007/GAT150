#include "Bullet.h"

#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Components/RigidBody.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Bullet)


void Bullet::update(float deltaTime) {

	

	Cpain::vec2 inputDirection{ 1, 0 };


	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(owner->transform.rotation)) * speed;
	
	if (m_rigidBody) {
		m_rigidBody->velocity = force;
	}

	owner->transform.position.x = Cpain::wrap(owner->transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	owner->transform.position.y = Cpain::wrap(owner->transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	float angle = owner->transform.rotation + Cpain::getReal(-20.0f, 20.0f);
	Cpain::vec2 velocity = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(angle));
	velocity *= Cpain::getReal(100.0f, 200.0f);

	Cpain::Particle particle;
	particle.position = owner->transform.position;
	particle.velocity = velocity;
	particle.color = Cpain::vec3{ 1.0f, Cpain::getReal(0.5f, 0.9f), 0.0f};
	particle.lifetime = 0.1f;
	Cpain::getEngine().getParticleSystem().addParticle(particle);
}

void Bullet::onCollision(Cpain::Actor* collider){
	if (owner->tag != collider->tag) {
		active = false;
	}
}

void Bullet::start() {
	m_rigidBody = owner->getComponent<Cpain::RigidBody>();
}
