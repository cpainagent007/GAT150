#pragma once

#include "../Math/Vector3.h"
#include "../Math/Transform.h"

#include <vector>

namespace Cpain {
	class Model {

	public:
		Model() = default;
		Model(const std::vector<vec2>& points, const vec3& color = { 1, 1, 1 })
			: m_points{ points }, m_color{ color } {
			calculateRadius();
		}

		void draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void draw(class Renderer& renderer, const Transform& transform);

		float getRadius() const {
			return m_radius;
		}

	private:
		void calculateRadius();

	private:
		std::vector<vec2> m_points;
		vec3 m_color{ 1, 1, 1 };
		float m_radius = 0.0f;
	};
}