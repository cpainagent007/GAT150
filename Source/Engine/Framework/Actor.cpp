#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace Cpain {
	FACTORY_REGISTER(Actor)
	
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

	Actor::Actor(const Actor& other) : Object{ other },
	tag{ other.tag }, lifespan{ other.lifespan }, transform{ other.transform }
	{
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->clone().release()));
			addComponent(std::move(clone));
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

	void Actor::read(const Json::value_t& value) {
		Object::read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);

		if(JSON_HAS(value, transform)) transform.read(JSON_GET(value, transform));

		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);


				auto component = Factory::instance().create<Component>(type);
				component->read(componentValue);

				addComponent(std::move(component));
			}
		}
	}

}
