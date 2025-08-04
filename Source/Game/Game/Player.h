#pragma once

#include "Framework/Actor.h"

class Player : public Cpain::Actor {
public:
	enum class Weapon {
		Rocket,
		Rapid,
		Super,
	};

public:
	const float rocketRate = 0.5f;
	const float rapidRate = 0.05f;
	const float superRate = 2.5f;
	const float bombRate = 1.0f;

	float shipSpeed = 200.0f;
	float rotationSpeed = 180.0f;
	float fireRate = 0.0f;
	float fireTimer = 0.0f;
	float thrust;
	Weapon weapon;


public:
	Player() = default;
	Player(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {}

	void update(float deltaTime) override;

	void onCollision(Actor* collider) override;

	bool getMoving();

};