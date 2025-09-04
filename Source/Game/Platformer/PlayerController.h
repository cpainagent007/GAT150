#pragma once

#include "Framework/Component.h"
#include "Physics/Collidable.h"

class PlayerController : public Cpain::Component, public Cpain::ICollidable {
public:
	float speed = 0.0f;
	float maxSpeed = 0.0f;
	float jump = 0.0f;
	float fireRate = 0.0f;
	float fireTimer = 0.0f;

	float jumpCooldown = 1.5f;
	float jumpTimer = 0.0f;

	bool jumped = false;

	Cpain::RigidBody* m_rigidBody = nullptr;

public:
	PlayerController() = default;

	CLASS_PROTOTYPE(PlayerController)

	void update(float deltaTime) override;

	void onCollision(class Cpain::Actor* collider) override;

	void read(const Cpain::Json::value_t& value);

	void start() override;
};