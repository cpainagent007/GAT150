#pragma once

#include "../Core/StringHelper.h"
#include "Resource.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace Cpain {
	class ResourceManager {
	public:
		template <typename T, typename ... TArgs>
		res_t<T> get(const std::string& name, TArgs&& ... args);

		static ResourceManager& instance() {
			static ResourceManager instance;
			return instance;
		}
		
	private:
		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> m_resources;

	};

	template <typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::get(const std::string& name, TArgs&& ... args) {
		std::string key = toLower(name);

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
		if (resource->load(key, std::forward<TArgs>(args)...) == false) {
			std::cerr << "Cannot load resource: " << key << std::endl;
			return res_t<T>();
		}

		m_resources[key] = resource;

		return resource;
	}

	
}