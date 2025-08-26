#include "EventManager.h"

namespace Cpain {
	void EventManager::addObserver(const Event::id_t& id, IObserver& observer) {
		m_observers[toLower(id)].push_back(&observer);

	}

	void EventManager::removeObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;

		for (auto& eventType : m_observers) {
			auto& observers = eventType.second;

			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::notify(const Event& event) {
		auto iter = m_observers.find(toLower(event.id));
		if (iter != m_observers.end()) {
			auto& observers = iter->second;
			for (auto& observer : observers) {
				observer->onNotify(event);
			}
		} else {
			Logger::Warning("Could not notify of event: {}", event.id);
		}

	}
}
