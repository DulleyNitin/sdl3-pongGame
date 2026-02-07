#ifndef APPLICATION_H
#define APPLICATION_H

#include "ball.h"
#include "paddle.h"
#include "UImanager.h"

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>


struct application {
  bool mRunning = true;
  int mFps;
  int mScore1;
  int mScore2;
  int mLogicalWidth, mLogicalHeight;
  SDL_Window *mWindow = nullptr;
  SDL_Renderer *mRenderer = nullptr;
  SDL_Texture *mTextTexture = nullptr;
  TTF_Font *font = nullptr;
  Ball ball;
  paddle pad1;
  paddle pad2;
  paddleIntent pad1Intent;
  paddleIntent pad2Intent;
  paddleBindings pad1KeyBindings;
  paddleBindings pad2KeyBindings;
  UImanager hud;

  application();
  ~application();
  void mainLoop();
private:
  void tick(float, int);
  void input();
  void update(float);
  void render(int);
};

#endif 
