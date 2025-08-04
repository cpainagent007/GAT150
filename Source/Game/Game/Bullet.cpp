#include "Bullet.h"

#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"

void Bullet::update(float deltaTime) {
	Cpain::vec2 inputDirection{ 1, 0 };


	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(transform.rotation)) * speed;
	velocity += force;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	float angle = transform.rotation + Cpain::getReal(-20.0f, 20.0f);
	Cpain::vec2 velocity = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(angle));
	velocity *= Cpain::getReal(100.0f, 200.0f);

	Cpain::Particle particle;
	particle.position = transform.position;
	particle.velocity = velocity;
	particle.color = Cpain::vec3{ 1.0f, Cpain::getReal(0.5f, 0.9f), 0.0f};
	particle.lifetime = 0.1f;
	Cpain::getEngine().getParticleSystem().addParticle(particle);


	Actor::update(deltaTime);
}

void Bullet::onCollision(Actor* collider){
	if (tag != collider->tag) {
		active = false;
	}
}
