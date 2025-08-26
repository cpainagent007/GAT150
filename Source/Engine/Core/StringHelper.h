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

	inline bool equalsIgnoreCase(const std::string strA, const std::string strB) {
		if (strA.length() != strB.length()) return false;

		return std::equal(strA.begin(), strA.end(), strB.begin(), [](char a, char b) {
			return (std::tolower(a) == std::tolower(b));
		});
	}
}