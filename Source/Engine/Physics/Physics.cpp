#include "Physics.h"

namespace Cpain {
	float ms_pixelsPerUnit = 48.0f;

	bool Physics::initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::shutdown() {
		b2DestroyWorld(m_worldId);
	}

	void Physics::update(float deltaTime) {
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
	}
}