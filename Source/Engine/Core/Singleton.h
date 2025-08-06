#pragma once

namespace Cpain {
	template <typename T>
	class Singleton {
	public:
		Singleton(const Singleton&) = delete;

		Singleton& operator = (const Singleton&) = delete;

		static T& instance() {
			static T instance;
			return instance;
		}

	protected:
		Singleton() {}
	};
}