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
		std::erase_if(m_actors, [](auto& actor) {
			return (!actor->active);
		});
		
		// Collision
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {

				continue;

				if (actorA == actorB || (!actorA->active) || (!actorB->active)) continue;

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

	void Scene::addActor(std::unique_ptr<Actor> actor, bool start) {
		actor->scene = this;
		if (start) actor->start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::removeAll(bool force) {
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if (!(*iter)->persistent || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::read(const Json::value_t& value) {
		if (JSON_HAS(value, prototypes)) {
			for (auto& protoValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::instance().create<Actor>("Actor");
				actor->read(protoValue);

				std::string name = actor->name;
				Factory::instance().registerPrototype<Actor>(name, std::move(actor));
			}
		}

		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::instance().create<Actor>("Actor");
				actor->read(actorValue);

				addActor(std::move(actor), false);
			}
		}
	}

	bool Scene::load(const std::string& sceneName) {
		Json::doc_t document;
		if (!Json::load(sceneName, document)) {
			Logger::Error("Could not load scene {}", sceneName);
			return false;
		}
		read(document);

		for (auto& actor : m_actors) {
			actor->start();
		}

		return true;
	}

}


