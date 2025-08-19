#include "EnginePCH.h"

namespace Cpain {
	void Object::read(const Json::value_t& value) {
		JSON_READ(value, name);
		JSON_READ(value, active);
	}
}

