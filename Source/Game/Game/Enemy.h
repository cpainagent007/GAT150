#pragma once

#include "Framework/Component.h"


class Enemy : public Cpain::Component {
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

	void onCollision(class Cpain::Actor* collider);

	void update(float deltaTime) override;

};