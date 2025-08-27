#pragma once

#include "Framework/Component.h"

class Bullet : public Cpain::Component, public Cpain::ICollidable {
public:
	float speed = 500;
	Cpain::RigidBody* m_rigidBody = nullptr;

public:
	Bullet() = default;

	CLASS_PROTOTYPE(Bullet)

	void update(float deltaTime) override;

	void onCollision(class Cpain::Actor* collider) override;

	void start() override;
};