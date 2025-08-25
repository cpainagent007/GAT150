#pragma once

namespace Cpain {
	class EventManager : public Singleton<EventManager> {
	public:
		void addObserver(const Event::id_t& id, IObserver& observer);
		void removeObserver(IObserver& observer);
		void notify(const Event& event);

	private:
		std::map<Event::id_t, std::list<IObserver*>> m_observers;

	};
}