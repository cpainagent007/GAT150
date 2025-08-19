#pragma once
#include "Math.h"

#include <cassert>
#include <iostream>

namespace Cpain {
	template<typename T>
	struct Vector3 {

		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		Vector3 operator+(const Vector3& value) const { return Vector3{ x + value.x, y + value.y, z + value.z }; }
		Vector3 operator-(const Vector3& value) const { return Vector3{ x - value.x, y - value.y, z - value.z }; }

		Vector3 operator+(float scalar) const { return Vector3{ x + scalar, y + scalar, z + scalar }; }
		Vector3 operator-(float scalar) const { return Vector3{ x - scalar, y - scalar, z - scalar }; }
		Vector3 operator*(float scalar) const { return Vector3{ x * scalar, y * scalar, z * scalar }; }
		Vector3 operator/(float scalar) const { return Vector3{ x / scalar, y / scalar, z / scalar }; }

		Vector3& operator+=(const Vector3& value) { x += value.x; y += value.y; z += value.z; return *this; }
		Vector3& operator-=(const Vector3& value) { x -= value.x; y -= value.y; z += value.z; return *this; }

		Vector3& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
		Vector3& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
		Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
		Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

		T operator[](unsigned int index) const { return (&x)[index]; }
		T& operator[](unsigned int index) { return (&x)[index]; }

		/// <summary>
		/// Calculates the squared length (magnitude) of the vector.
		/// </summary>
		/// <returns>The sum of the squares of the x, y, and z components.</returns>
		float lengthSqrd() const { return (x * x) + (y * y) + (z * z); }

		/// <summary>
		/// Calculates the length by taking the square root of the value returned by lengthCbd().
		/// </summary>
		/// <returns>The length as a floating-point value.</returns>
		float length() const { return sqrtf(lengthSqrd()); }
	};

	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& vector) {
		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";

		return stream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& vector) {
		char ch = '\0';

		if (!(stream >> std::ws >> ch) || ch != '{') {
			return stream;
		}
		if (!(stream >> std::ws >> vector.x)) {
			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != ',') {
			return stream;
		}
		if (!(stream >> std::ws >> vector.y)) {
			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != ',') {
			return stream;
		}
		if (!(stream >> std::ws >> vector.z)) {
			return stream;
		}
		if (!(stream >> std::ws >> ch) || ch != '}') {
			return stream;
		}

		return stream;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}