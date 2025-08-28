#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {

    // Set Directory

	Cpain::setCurrentDirectory("Assets/Platformer");
    Cpain::Logger::Info("Current Directory {}", Cpain::getCurrentDirectory());

    // Testing
    // ----------

    //return 0;

    // ----------

    // Initialize SDL/Renderer

	Cpain::getEngine().initialize();

    // Initialize Game

	std::unique_ptr<Cpain::Game> game = std::make_unique<PlatformerGame>();
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