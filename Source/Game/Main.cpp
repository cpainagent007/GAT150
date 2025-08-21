#include "Audio/AudioSystem.h"

#include "Core/File.h"
#include "Core/Random.h"
#include "Core/Time.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"

#include "Input/InputSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Resources/ResourceManager.h"

#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"

#include "Engine.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>



int main(int argc, char* argv[]) {

    // Set Directory

	Cpain::setCurrentDirectory("Assets");
    Cpain::Logger::Info("Current Directory {}", Cpain::getCurrentDirectory());

    // Testing
    // ----------

    //return 0;

    // ----------

    // Initialize SDL/Renderer

	Cpain::getEngine().initialize();

    // Initialize Game

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->initialize();

	// Additional Initialization

    SDL_Event e;
    bool quit = false;
	
	// Main Loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		// Update Systems
        
		Cpain::getEngine().update();
		game->update(Cpain::getEngine().getTime().getDeltaTime());

        // Draw
        Cpain::vec3 color{ 0, 0, 0 };
		Cpain::getEngine().getRenderer().setColor(color.r, color.g, color.b);
        Cpain::getEngine().getRenderer().clear();

        game->draw(Cpain::getEngine().getRenderer());
        
        // Display
        Cpain::getEngine().getRenderer().present();
    }
	game->shutdown();
    game.release();
	Cpain::getEngine().shutdown();

    return 0;
}