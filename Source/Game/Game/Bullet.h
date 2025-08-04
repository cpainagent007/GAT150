#pragma once

#include "Framework/Actor.h"

class Bullet : public Cpain::Actor {
public:
	float speed = 100.0f;

public:
	Bullet() = default;
	Bullet(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {}

	void update(float deltaTime) override;

	void onCollision(Actor* collider) override;

};