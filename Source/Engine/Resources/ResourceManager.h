#pragma once

#include "../Core/StringHelper.h"
#include "../Core/Singleton.h"
#include "Resource.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace Cpain {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template <typename T, typename ... Args>
		res_t<T> get(const std::string& name, Args&& ... args);

		template <typename T, typename ... Args>
		res_t<T> getByID(const std::string& id, const std::string& name, Args&& ... args);
		
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> m_resources;

	};

	template <typename T, typename ... Args>
	inline res_t<T> ResourceManager::get(const std::string& name, Args&& ... args) {
		return getByID<T>(name, name, std::forward<Args>(args)...);
	}

	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::getByID(const std::string& id, const std::string& name, Args && ...args) {
		std::string key = toLower(id);

		auto iter = m_resources.find(key);
		if (iter != m_resources.end()) {
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);
			if (resource == nullptr) {
				std::cerr << "Resource type mismatch: " << key << std::endl;
				return res_t<T>();
			}

			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->load(name, std::forward<Args>(args)...) == false) {
			std::cerr << "Cannot load resource: " << name << std::endl;
			return res_t<T>();
		}

		m_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& resources() { return ResourceManager::instance(); }
	
}