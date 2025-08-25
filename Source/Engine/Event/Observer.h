#pragma once

namespace Cpain {
	class IObserver {
		virtual ~IObserver() = default;

		virtual void onNotify(const Event& event) = 0;
	};
}