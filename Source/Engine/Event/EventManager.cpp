#include "EventManager.h"

namespace Cpain {
	void EventManager::addObserver(const Event::id_t& id, IObserver& observer) {
		m_observers[toLower(id)].push_back(&observer);

	}

	void EventManager::removeObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;

		for (auto& eventType : m_observers) {
			auto observers = eventType.second;

			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::notify(const Event& event) {

	}
}
