#pragma once

#include "../Core/StringHelper.h"
#include "../Core/Factory.h"

#include <list>
#include <vector>
#include <memory>
#include <string>

namespace Cpain {
	class Actor;
	class Game;

	class Scene : public ISerializable {
	public:
		Scene(Game* game) : m_game{ game } {}

		void update(float deltaTime);
		void draw(class Renderer& renderer);
		void addActor(std::unique_ptr<class Actor>, bool start = true);

		bool load(const std::string& sceneName);

		void removeAll(bool force = false);

		template<typename T = Actor>
		T* getActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> getActorByTag(const std::string& tag);

		class Game* getGame() const { return m_game; }

		void read(const Json::value_t& value) override;

	private:
		class Game* m_game = nullptr;
		std::list<std::unique_ptr<class Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::getActorByName(const std::string& name) {
		for (auto& actor : m_actors) {
			if (toLower(actor->name) == toLower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::getActorByTag(const std::string& tag) {
		std::vector<T*> actorsWithTag;
		for (auto& actor : m_actors) {
			if (toLower(actor->tag) == toLower(tag)) {
				T* object = dynamic_cast<T*>(actor);
				if (object) {
					actorsWithTag.push_back(object);
				}
			}
		}
		return actorsWithTag;
	}
}