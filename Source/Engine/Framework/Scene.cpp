#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace Cpain {

	void Scene::update(float deltaTime) {
		// Update
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->update(deltaTime);
			}
			
		}

		// Remove inactive
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if ((*iter)->active == false) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// Collision
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->active == false) || (actorB->active == false)) continue;

				auto colliderA = actorA->getComponent<ColliderComponent>();
				auto colliderB = actorB->getComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->checkCollision(*colliderB)) {
					actorA->onCollision(actorB.get());
					actorB->onCollision(actorA.get());
				}
			}
		}
	}

	void Scene::draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->draw(renderer);
			}

		}
	}

	void Scene::addActor(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::removeAll() {
		m_actors.clear();
	}

	void Scene::read(const Json::value_t& value) {
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::instance().create<Actor>("Actor");
				actor->read(actorValue);

				addActor(std::move(actor));
			}
		}
	}
}


