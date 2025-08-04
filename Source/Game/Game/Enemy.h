#pragma once

#include "Framework/Actor.h"

class Enemy : public Cpain::Actor {
public:
	enum class Type {
		Basic,
		Fast,
		Shooter,
		Mega
	};

	Type type = Type::Basic;

public:
	float fireTimer = 0.0f;
	float fireRate = 1.0f;
	float speed = 100.0f;
public:
	Enemy() = default;
	Enemy(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {
	}

	void update(float deltaTime) override;

	void onCollision(Actor* collider) override;

};