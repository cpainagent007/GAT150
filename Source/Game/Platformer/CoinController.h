#pragma once

#include "Framework/Actor.h"
#include "Framework/Component.h"
#include "Physics/Collidable.h"

class CoinController : public Cpain::Component, public Cpain::ICollidable, public Cpain::IObserver {
public:
    float score = 1.0f;

	Cpain::RigidBody* m_rigidBody = nullptr;

public:
	CoinController() = default;

	CLASS_PROTOTYPE(CoinController)

	void update(float deltaTime) override;

	void onCollision(class Cpain::Actor* collider) override;

	void read(const Cpain::Json::value_t& value);

	void start() override;

	void onNotify(const Cpain::Event& event) override;
};