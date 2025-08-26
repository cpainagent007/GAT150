#pragma once

namespace Cpain {
	class IObserver {
	public:
		virtual ~IObserver();

		virtual void onNotify(const Event& event) = 0;
	};
}