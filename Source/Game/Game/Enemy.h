#pragma once

#include "Framework/Component.h"


class Enemy : public Cpain::Component, public Cpain::ICollidable, public Cpain::IObserver {
public:
	// Enemy Type Enumeration
	/*
		enum class Type {
		Basic,
		Fast,
		Shooter,
		Mega
	};

	Type type = Type::Basic;
	*/


public:
	float fireTimer = 0.0f;
	float fireRate = 1.0f;
	float speed = 100.0f;

	Cpain::RigidBody* m_rigidBody = nullptr;

public:
	Enemy() = default;

	CLASS_PROTOTYPE(Enemy)

	void onCollision(class Cpain::Actor* collider) override;

	void update(float deltaTime) override;

	void start() override;

	void onNotify(const Cpain::Event& event);
};