#include "Observer.h"

namespace Cpain {
	Cpain::IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}