#pragma once

#include "Json.h"

namespace Cpain {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		virtual void read(const Json::value_t& value) = 0;
	};
}