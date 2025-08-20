#include "EnginePCH.h"

namespace Cpain {
	void Object::read(const rapidjson::Value& value) {
		JSON_READ(value, name);
		JSON_READ(value, active);
	}
}

