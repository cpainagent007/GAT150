#pragma once
#include <chrono>

namespace Cpain {
	class Time {

	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			m_startTime = clock::now();
			m_frameTime = clock::now();
		}

		void tick();
		void reset() { m_startTime = clock::now(); }

		float getTime() const { return m_time; }
		float getDeltaTime() const { return m_deltaTime; }

	private:
		clock::time_point m_startTime;
		clock::time_point m_frameTime;
		float m_time = 0.0f;
		float m_deltaTime = 0.0f;

	};
}
