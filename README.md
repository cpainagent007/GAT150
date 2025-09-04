# BatStomper
<img width="133" height="239" alt="title" src="https://github.com/user-attachments/assets/3f51d097-e5c2-452d-8725-e7e77c255ad8" />

---
BatStomper is a game made in the GAT150 engine. It is a physics-based game where the player runs around and stomps bats.

<img width="1102" height="985" alt="image" src="https://github.com/user-attachments/assets/874953c5-5d66-4734-ab94-956c2052bb4c" />

---
The GAT150 engine contains important game-creation files such as audio, events, input, and rendering, as well as other files such as resource managers, file reading, JSON support, etc.

---
Follow common procedure in Visual Studio for building the project. To run the project, ensure that the "Game" project is selected as startup, and code block: <pre> ```std::unique_ptr<Cpain::Game> game = std::make_unique<PlatformerGame>();``` </pre> is implemented in main before code block: <pre> ```game->initialize();``` </pre>

---
External libraries used for project:  
- SDL3  
- SDL3_image  
- FMOD  
- rapidJSON  
- box2D  
