#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace Cpain {

	void Scene::update(float deltaTime) {
		// Update
		for (auto& actor : m_actors) {
			actor->update(deltaTime);
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

				float distance = (actorA->transform.position - actorB->transform.position).length();
				if (distance <= actorA->getRadius() + actorB->getRadius()) {
					actorA->onCollision(actorB.get());
					actorB->onCollision(actorA.get());
				}

			}
		}
	}

	void Scene::draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->draw(renderer);
		}
	}

	void Scene::addActor(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::removeAll() {
		m_actors.clear();
	}
}


