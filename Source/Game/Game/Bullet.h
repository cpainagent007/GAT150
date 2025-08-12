#pragma once

#include "Framework/Actor.h"

class Bullet : public Cpain::Actor {
public:
	float speed = 100.0f;

public:
	Bullet() = default;
	Bullet(const Cpain::Transform& transform) :
		Cpain::Actor{ transform } {}

	void update(float deltaTime) override;

	void onCollision(Actor* collider) override;

};