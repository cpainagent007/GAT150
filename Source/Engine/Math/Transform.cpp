#include "EnginePCH.h"

namespace Cpain {
	void Transform::read(const Json::value_t& value) {
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);
	}
}

