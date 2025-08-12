#pragma once

#include "../Math/Transform.h"
#include "../Renderer/Model.h"
#include "Scene.h"
#include "../Renderer/Texture.h"
#include "Object.h"

#include <memory>
#include <vector>
#include <string>

namespace Cpain {
	class Actor : public Object {
	public:
		std::string tag;

		bool active = true;
		float lifespan = 0.0f;

		Transform transform;
		Scene* scene = nullptr;

	public:
		Actor() = default;
		Actor(const Transform& transform)
			: transform{ transform } {}

		virtual void update(float deltaTime);
		virtual void draw(class Renderer& renderer);

		Transform& getTransform() { return transform; }

		virtual void onCollision(Actor* collider) = 0;

		void addComponent(std::unique_ptr<class Component> component);

		template <typename T>
		T* getComponent();

		template <typename T>
		std::vector<T*> getComponents();

	protected:
		std::vector<std::unique_ptr<class Component>> m_components;
	};

	template <typename T>
	inline T* Actor::getComponent() {
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}

	template <typename T>
	inline std::vector<T*> getComponents() {
		std::vector<T*> results;

		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}

		return results;
	}
}