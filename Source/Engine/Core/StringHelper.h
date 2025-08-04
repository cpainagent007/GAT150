#pragma once

#include <string>

namespace Cpain {

	inline std::string toLower(const std::string str) {
		std::string result = str;

		for (char& c : result) {
			c = std::tolower(c);
		}

		return str;
	}
	inline std::string toUpper(std::string str) {
		for (char& c : str) {
			c = std::toupper(c);
		}
		return str;
	}

}