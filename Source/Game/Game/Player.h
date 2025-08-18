#pragma once

#include "Framework/Component.h"

class Player : public Cpain::Component {
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

	void update(float deltaTime) override;

	void onCollision(class Actor* collider);

	bool getMoving();

};