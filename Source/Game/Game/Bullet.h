#pragma once

#include "Framework/Component.h"

class Bullet : public Cpain::Component {
public:
	float speed = 100.0f;

public:
	Bullet() = default;

	void update(float deltaTime) override;

	void onCollision(class Cpain::Actor* collider);

};