#pragma once
#include "Math.h"

namespace Cpain {
	template<typename T>
	struct Vector2 {

		union {
			struct { T x, y; };
			struct { T u, v; };
		};

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		Vector2 operator+(const Vector2& value) const { return Vector2{ x + value.x, y + value.y }; }
		Vector2 operator-(const Vector2& value) const { return Vector2{ x - value.x, y - value.y }; }
		//Vector2 operator*(const T& value) const { return Vector2{ x * value, y * value }; }
		//Vector2 operator/(const T& value) const { return Vector2{ x / value, y / value }; }

		Vector2 operator+(float scalar) const { return Vector2{ x + scalar, y + scalar }; }
		Vector2 operator-(float scalar) const { return Vector2{ x - scalar, y - scalar }; }
		Vector2 operator*(float scalar) const { return Vector2{ x * scalar, y * scalar }; }
		Vector2 operator/(float scalar) const { return Vector2{ x / scalar, y / scalar }; }

		Vector2& operator+=(const Vector2& value) { x += value.x; y += value.y; return *this; }
		Vector2& operator-=(const Vector2& value) { x -= value.x; y -= value.y; return *this; }
		//Vector2& operator*=(const T& value) { x *= value; y *= value; return *this; }
		//Vector2& operator/=(const T& value) { x /= value; y /= value; return *this; }

		Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
		Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
		Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
		Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

		T operator[](unsigned int index) const { return (&x)[index]; }
		T& operator[](unsigned int index) { return (&x)[index]; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a 2D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components, representing the squared length of the vector.</returns>
		float lengthSqrd() const { return (x * x) + (y * y); }

		/// <summary>
		/// Calculates the length (magnitude) using the square root of the squared length.
		/// </summary>
		/// <returns>The length as a floating-point value.</returns>
		float length() const { return sqrtf(lengthSqrd()); }

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the original vector scaled to have a length of 1.</returns>
		Vector2 normalized() const { return *this / length(); }

		/// <summary>
		/// Returns the angle in radians between the positive x-axis and the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
		float angle() const { return atan2f(y, x); }

		/// <summary>
		/// Returns a new Vector2 that is the result of rotating this vector by a specified angle in radians.
		/// </summary>
		/// <param name="radians">The angle to rotate the vector, in radians.</param>
		/// <returns>A new Vector2 representing the rotated vector.</returns>
		Vector2 rotate(float radians) const { 
			Vector2 v;

			v.x = x * cosf(radians) - y * sinf(radians);
			v.y = x * sinf(radians) + y * cosf(radians);

			return v;
		}

		static float dot(const Vector2 a, const Vector2 b) {
			return (a.x * b.x) + (a.y * b.y);
		}

		static float cross(const Vector2 a, const Vector2 b) {
			return a.x * b.y - a.y * b.x;
		}

		static float angleBetween(const Vector2 a, const Vector2 b) {
			return acosf(dot(a, b));
		}

		static float signedAngleBetween(const Vector2& a, const Vector2& b) {
			float dotProd = dot(a, b);
			float crossProd = cross(a, b);
			return std::atan2(crossProd, dotProd);
		}


	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}