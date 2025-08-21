#pragma once

#include "../Core/Serializable.h"
#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> clone() { return std::make_unique<classname>(*this); }

namespace Cpain {
	class Object : public Serializable {
	public:
		std::string name;
		bool active = true;

	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::unique_ptr<Object> clone() = 0;

		void read(const rapidjson::Value& value) override;
	};
}