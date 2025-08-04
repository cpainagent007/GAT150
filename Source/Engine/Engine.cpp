#include "Engine.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"

namespace Cpain {

	bool Engine::initialize() {
		m_particleSystem = std::make_unique<Cpain::ParticleSystem>();
		m_particleSystem->initialize();

		m_renderer = std::make_unique<Cpain::Renderer>();
		m_renderer->initialize();
		m_renderer->createWindow("Cpain Engine", 1280, 1024);

		m_input = std::make_unique<InputSystem>();
		m_input->initialize();

		m_audio = std::make_unique<AudioSystem>();
		m_audio->initialize();

		return true;
	}

	void Engine::shutdown() {
		m_audio->shutdown();
		m_input->shutdown();
		m_renderer->shutdown();
		m_particleSystem->shutdown();
	}

	void Engine::update() {
		m_time.tick();
		m_audio->update();
		m_input->update();
		m_particleSystem->update(m_time.getDeltaTime());
	}

	void Engine::draw() {

	}	

	Engine& getEngine() {
		static Engine engine;
		return engine;
	}
}