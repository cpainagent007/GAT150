#pragma once

#include "Observer.h"

#define OBSERVER_ADD(event_id)				Cpain::EventManager::instance().addObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				Cpain::EventManager::instance().removeObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	Cpain::EventManager::instance().notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				Cpain::EventManager::instance().notify({ #event_id, true })

namespace Cpain {
	class EventManager : public Singleton<EventManager> {
	public:
		void addObserver(const Event::id_t& id, IObserver& observer);
		void removeObserver(IObserver& observer);
		void notify(const Event& event);
		void removeAll() { m_observers.clear(); }

	private:
		std::map<Event::id_t, std::list<IObserver*>> m_observers;

	};
}