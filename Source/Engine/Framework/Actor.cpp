#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace Cpain {
		
	void Actor::update(float deltaTime) {
		if (!active) return;

		if (lifespan > 0) {
			lifespan -= deltaTime;
			if (lifespan <= 0) {
				active = false;
				return;
			}
			active = (lifespan > 0);
		}

		for (auto& component : m_components) {
			if (component->active) {
				component->update(deltaTime);
			}
		}

		
	}

	void Actor::draw(Renderer& renderer) {
		if (!active) return;

		for (auto& component : m_components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->draw(renderer);
				}
			}
		}
	}

	void Actor::addComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		m_components.push_back(std::move(component));
	}

}
