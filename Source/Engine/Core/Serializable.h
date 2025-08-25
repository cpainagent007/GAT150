#pragma once

#include "Json.h"

namespace Cpain {
	class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual void read(const Json::value_t& value) = 0;
	};
}