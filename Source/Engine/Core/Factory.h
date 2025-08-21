#pragma once

#include "Framework/Object.h"
#include "Singleton.h"
#include "StringHelper.h"
#include "Logger.h"
#include "Framework/Actor.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname {         \
public:                             \
    Register##classname() {         \
        Cpain::Factory::instance().registerItem<classname>(#classname); \
    }                               \
};									\
Register##classname register_instance;

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

	template <typename T>
		requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}

		std::unique_ptr<Object> create() override {
			return m_prototype->clone();
		}

	private:
		std::unique_ptr<T> m_prototype;

	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void registerItem(const std::string& name);

		template<typename T>
		requires std::derived_from<T, Object>
		void registerPrototype(const std::string& name, std::unique_ptr<T> prototype);

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
	inline void Factory::registerPrototype(const std::string& name, std::unique_ptr<T> prototype) {
		std::string key = toLower(name);
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));

		Logger::Info("{} (prototype) added to factory.", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::create(const std::string& name) {
		std::string key = toLower(name);
		auto iter = m_registry.find(key);

		if (iter != m_registry.end()) {
			auto object = iter->second->create();
			T* derived = dynamic_cast<T*>(object.get());

			if (derived) {
				object.release();
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Factory object type mismatch: {}", name);

		} else {
			Logger::Error("Could not create factory object: {}", name);
		}

		return nullptr;
	}

	template <typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> instantiate(const std::string& name) {
		Factory::instance().create<T>(name);
	}

	template <typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		Factory::instance().create<T>(name) {
			Transform{ position, rotation, scale };
		};
	}

	template <typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> instantiate(const std::string& name, const Transform& transform) {
		Factory::instance().create<T>(name) { transform };
	}

}