#pragma once

#include "Framework/Object.h"
#include "Singleton.h"
#include "StringHelper.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname {         \
public:                             \
    Register##classname() {         \
        Cpain::Factory::instance().registerItem<classname>(#classname); \
    }                               \
};

namespace Cpain {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> create() = 0;
	};

	template <typename T>
	requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> create() override {
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void registerItem(const std::string& name);

		template<typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;

	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::registerItem(const std::string& name) {
		std::string key = toLower(name);
		m_registry[key] = std::make_unique<Creator<T>>();

		Logger::Info("{} added to factory.", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::create(const std::string& name) {
		std::string key = toLower(name);
		auto iter = m_registry.find(key);

		if (iter != m_registry.end()) {
			return iter->second->create();
		}

		Logger::Error("Could not create factory object: {}", name);

		return nullptr;
	}
}