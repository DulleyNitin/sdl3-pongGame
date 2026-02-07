#include "app.h"
#include "ball.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>

application::application()
  //initialization of pad1(player 1)
  : ball(),
    pad1(10.f, 275.f) , //this is a functionality of c++ called initializer list as members as to be created before constructor
    pad2(930.f, 275.f) ,
    hud()
{
  //initialization of video component of sdl3
  int rc = SDL_Init(SDL_INIT_VIDEO);
  if ( rc < 0) { //changed to this way because only return result < 0 is fatal and here i am getting 1 as return which is fine
                 //will look at this later
    SDL_Log("video initialization failed: %s", SDL_GetError());
  }

  //initializing a window
  mWindow = SDL_CreateWindow("ping pong" ,1920 ,1080 , SDL_WINDOW_RESIZABLE);
  if(!mWindow) {
    SDL_Log("window initialization failed");
  }

  //initializing a renderer
  mRenderer = SDL_CreateRenderer(mWindow, nullptr);
  if(!mRenderer) {
    SDL_Log("Renderer initialization failed");
  }
  mLogicalWidth = 960;
  mLogicalHeight = 540;
  SDL_SetRenderLogicalPresentation(mRenderer, mLogicalWidth, mLogicalHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  //key bindings for paddle 1
  pad1KeyBindings.up = SDL_SCANCODE_W;
  pad1KeyBindings.down = SDL_SCANCODE_S;

  //key bindings for paddle 2
  pad2KeyBindings.up = SDL_SCANCODE_UP;
  pad2KeyBindings.down = SDL_SCANCODE_DOWN;

  //setting the score of players
  mScore1 = 0;
  mScore2 = 0;
}
application::~application() {
  if(mRenderer) {
    SDL_DestroyRenderer(mRenderer);
  }
  if(mWindow) {
    SDL_DestroyWindow(mWindow);
  }
  SDL_Quit();
}

void application::tick(float dt, int fps) {
  input();
  update(dt);
  render(fps);
}

void application::input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    //if window is closed
    if(event.type == SDL_EVENT_QUIT) {
      mRunning = false;
    }
  const bool* keys = SDL_GetKeyboardState(nullptr);

    //reset intent every frame
    pad1Intent = {};
    pad2Intent = {};

    // pad1
    pad1Intent.moveUp = keys[pad1KeyBindings.up];
    pad1Intent.moveDown = keys[pad1KeyBindings.down];

    // pad2
    pad2Intent.moveUp = keys[pad2KeyBindings.up];
    pad2Intent.moveDown = keys[pad2KeyBindings.down];
  
 }
}
  
void application::update(float dt) {
  BallResult result = ball.update(pad1, pad2, mLogicalHeight, mLogicalWidth , dt);
  if(result == BallResult::ballLeftOut) {
    mScore2++;
  }
  if(result == BallResult::ballRightOut) {
    mScore1++;
  }
  pad1.update(pad1Intent, mLogicalHeight, dt);
  pad2.update(pad2Intent, mLogicalHeight, dt);
}

void application::render(int fps) {
  //set color of renderer for a background
  SDL_SetRenderDrawColor(mRenderer, 141, 153, 174, 255); //for background 
  SDL_RenderClear(mRenderer);//clear the renderer with the draw color that was set 
  //more draw operation
  ball.render(mRenderer);
  pad1.render(mRenderer);
  pad2.render(mRenderer);

  //render the UI
  hud.render(mRenderer, mScore1, mScore2, fps);
  //SDL_FRect textRect = {100.f, 100.f, 250.f, 50.f};
  //SDL_RenderTexture(mRenderer, mTextTexture, 0, &textRect);

  SDL_RenderPresent(mRenderer);//present all the draw operation done on the renderer from the last call
}

void application::mainLoop() {
  const float targetFrameTime = 1.f/60.f; //target frame is 60 frames per second
  unsigned int lastTickTime = SDL_GetTicks(), startFrameTime, endFrameTime;
  unsigned int currentTime, lastTime = 0;// to get the fps
  int fps=0; //temporary to calculate the fps
  while(mRunning) {
    startFrameTime = SDL_GetTicks();
    float dt = (startFrameTime - lastTickTime) / 1000.f; //delta time
    lastTickTime = startFrameTime;

    if(dt > 0.05f) {
      dt = 0.05f;
    }
    tick(dt, mFps);
    endFrameTime = SDL_GetTicks();
    float frameTime = (endFrameTime - startFrameTime) / 1000.f;
    if(frameTime < targetFrameTime) {
      SDL_Delay( (targetFrameTime-frameTime) * 1000.f);
    }
    fps++;
    currentTime = SDL_GetTicks();
    if( currentTime > lastTime+1000 ) {
      lastTime = currentTime;
      mFps = fps;
      SDL_Log("fps = %d", fps);
      fps = 0;
    }
    
  }
}


