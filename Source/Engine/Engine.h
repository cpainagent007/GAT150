#pragma once

#include "Audio/AudioSystem.h"
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourceManager.h"
#include "Physics/Physics.h"

#include <memory>

namespace Cpain {
	class AudioSystem;
	class Time;
	class InputSystem;
	class Renderer;
	class ParticleSystem;

	class Engine : public Singleton<Engine> {
	public:


		bool initialize();
		void shutdown();

		void update();
		void draw();

		AudioSystem& getAudio() { return *m_audio; }
		Time& getTime() { return m_time; }
		InputSystem& getInput() { return *m_input; }
		Renderer& getRenderer() { return *m_renderer; }
		ParticleSystem& getParticleSystem() { return *m_particleSystem; }
		Physics& GetPhysics() { return *m_physics; }

	private:
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		std::unique_ptr<AudioSystem> m_audio;
		Time m_time;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<ParticleSystem> m_particleSystem;
		std::unique_ptr<Physics> m_physics;
		

	};

	inline Engine& getEngine() { return Engine::instance(); };

}