#include "Json.h"
#include "File.h"
#include "Logger.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Cpain::Json
{
    bool load(const std::string& filename, rapidjson::Document& document) {
        
        std::string buffer;
        if (!readTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}.", filename);
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        document.ParseStream(istream);

        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}.", filename);
            return false;
        }

        return true;
    }

    // READ (int)
    bool read(const rapidjson::Value& value, const std::string& name, int& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            Logger::Error("Could not read Json value (int): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }

    // READ (float)
    bool read(const rapidjson::Value& value, const std::string& name, float& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat()) {
            Logger::Error("Could not read Json value (float): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }

    // READ (bool)
    bool read(const rapidjson::Value& value, const std::string& name, bool& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
            Logger::Error("Could not read Json value (bool): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }

    // READ (string)
    bool read(const rapidjson::Value& value, const std::string& name, std::string& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            Logger::Error("Could not read Json value (string): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }

    // READ (vector2)
    bool read(const rapidjson::Value& value, const std::string& name, vec2& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
            Logger::Error("Could not read Json value (vec2): {}.", name);
            return false;
        }

        auto& array = value[name.c_str()];

        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }

    // READ (vector3)
    bool read(const rapidjson::Value& value, const std::string& name, vec3& data) {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3) {
            Logger::Error("Could not read Json value (vec3): {}.", name);
            return false;
        }

        auto& array = value[name.c_str()];

        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }
}