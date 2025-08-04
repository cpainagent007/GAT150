#pragma once
#include <algorithm>
#include <cmath>

namespace Cpain {

	constexpr float pi = 3.14159265359f;
	constexpr float twoPi = 2 * pi;
	constexpr float halfPi = pi / 2;

	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="rad">The angle in radians to convert.</param>
	/// <returns>The equivalent angle in degrees.</returns>
	constexpr float radToDeg(float rad) { return rad * (180 / pi); }

	/// <summary>
	/// Converts an angle from degrees to radians.
	/// </summary>
	/// <param name="deg">The angle in degrees to convert.</param>
	/// <returns>The angle in radians.</returns>
	constexpr float degToRad(float deg) { return deg * (pi / 180); }


	constexpr int wrap(int value, int min, int max) {
		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) {
			result += range;
		}

		return min + result;
	}

	
	inline float wrap(float value, float min, float max) {
		float range = max - min;
		float result = fmodf(value - min, range);
		if( result < 0) {
			result += range;
		}

		return min + result;
	}

	template<typename T>
	inline T sign(T value) {
		return (value < 0) ? (T)-1 : (value > 0) ? (T)1 : 0;
	}

	using std::min;
	using std::max;
	using std::clamp;

	using std::sqrt;
	using std::sqrtf;

	using std::sin;
	using std::sinf;

	using std::cos;
	using std::cosf;

	using std::tan;
	using std::tanf;
	using std::atan2;
	using std::atan2f;
}