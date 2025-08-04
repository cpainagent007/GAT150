#pragma once

#include "../Math/Vector2.h"

#include <vector>
#include <array>
#include <cassert>

namespace Cpain {
	class InputSystem {
	public:

		enum class MouseButton : uint8_t {
			Left,
			Middle,
			Right
		};

	public:

		InputSystem() = default;

		bool initialize();
		void shutdown();
		void update();

		/// <summary>
		/// Checks if a specific key is currently pressed.
		/// </summary>
		/// <param name="key">The key code to check, represented as an unsigned 8-bit integer.</param>
		/// <returns>true if the specified key is currently pressed; otherwise, false.</returns>
		bool getKeyDown(uint8_t key) const { return m_keyboardState[key]; }

		/// <summary>
		/// Checks if the specified key was pressed in the previous keyboard state.
		/// </summary>
		/// <param name="key">The key code (as an unsigned 8-bit integer) to check.</param>
		/// <returns>true if the key was down in the previous keyboard state; otherwise, false.</returns>
		bool getPrevKeyDown(uint8_t key) const { return m_prevKeyboardState[key]; }

		/// <summary>
		/// Determines if a specific key was pressed in the current frame.
		/// </summary>
		/// <param name="key">The key code (as an unsigned 8-bit integer) to check.</param>
		/// <returns>true if the specified key was pressed in the current frame; otherwise, false.</returns>
		bool getKeyPressed(uint8_t key) const { return !m_prevKeyboardState[key] && m_keyboardState[key]; }

		/// <summary>
		/// Checks if a specific key was released since the last update.
		/// </summary>
		/// <param name="key">The key code (as an unsigned 8-bit integer) to check for release.</param>
		/// <returns>true if the key was released (pressed in the previous state and not pressed in the current state); false otherwise.</returns>
		bool getKeyReleased(uint8_t key) const { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		/// <summary>
		/// Retrieves the current mouse position.
		/// </summary>
		/// <returns>A constant reference to a CVec2::vec2 object representing the current mouse position.</returns>
		const vec2& getMousePosition() const { return m_mousePosition; }

		/// <summary>
		/// Returns the previous mouse position.
		/// </summary>
		/// <returns>A constant reference to a CVec2::vec2 object representing the previous mouse position.</returns>
		const vec2& getPrevMousePosition() const { return m_prevMousePosition; }


		bool getMouseButtonDown(MouseButton button) { return m_mouseButtonState[(uint8_t)button]; }


		bool getPrevMouseButtonDown(MouseButton button) { return m_prevMouseButtonState[(uint8_t)button]; }


		bool getMouseButtonPressed(MouseButton button) {
			return !m_prevMouseButtonState[(uint8_t)button] && m_mouseButtonState[(uint8_t)button];
		}


		bool getMouseButtonReleased(MouseButton button) {
			return m_prevMouseButtonState[(uint8_t)button] && !m_mouseButtonState[(uint8_t)button];
		}

	private:

		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;

		vec2 m_mousePosition{ 0, 0 };
		vec2 m_prevMousePosition{ 0, 0 };

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool, 3> m_prevMouseButtonState{ false, false, false };
	};
}