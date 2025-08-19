#pragma once

namespace Cpain {
	class Object : public Serializable {
	public:
		std::string name;
		bool active = true;

	public:
		Object() = default;
		virtual ~Object() = default;

		void read(const Json::value_t& value) override;
	};
}