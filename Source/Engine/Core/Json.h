#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <rapidjson/document.h>
#include <string>

#define JSON_READ(value, data) Cpain::Json::read(value, #data, data)

namespace Cpain::Json
{
	bool load(const std::string& filename, rapidjson::Document& document);

	bool read(const rapidjson::Value& value, const std::string& name, int& data);
	bool read(const rapidjson::Value& value, const std::string& name, float& data);
	bool read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool read(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool read(const rapidjson::Value& value, const std::string& name, vec2& data);
	bool read(const rapidjson::Value& value, const std::string& name, vec3& data);
}