# SDL3 Pong
A simple Pong clone written in **C++ using SDL3**.  
This project was built as a learning exercise to understand game loop design, collision detection, and modular game architecture.

## Features
- Two player Pong gameplay
- AABB collision detection with overlap resolution
- Frame rate independent movement using delta time
- FPS limiting
- Logical resolution scaling
- Score UI using SDL3_ttf
- Modular object structure (Ball, Paddle, UI Manager)

## Controls
  **Player 1**
- Move Up: `W`
- Move Down: `S`
  **Player 2**
- Move Up: `Up Arrow`
- Move Down: `Down Arrow`

## Project Structure

main.cpp → Program entry
app.* → Main application loop and game logic
ball.* → Ball physics and collision
paddle.* → Paddle movement and input handling
UImanager.* → Score and FPS text rendering
build.sh → Build script
---

## Requirements
- C++ Compiler (g++)
- SDL3
- SDL3_ttf

## Build Instructions
Clone the repository:
- git clone https://github.com/DulleyNitin/sdl3-pongGame.git
  cd pong-sdl3
- Build the project: ./build.sh
- run the project: ./pong

## What I Learned From This Project
- Game loop design
- Separation of game logic and rendering
- Collision detection and response
- Frame rate independent movement
- Basic UI rendering in SDL
- Modular C++ project organization

## Future Improvements (Planned / Possible)
- Sound effects
- Pause and game state system
- Better bounce angles based on paddle hit position
- Improved UI styling
- Physics polishing (sub-stepping / CCD)
