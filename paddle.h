#ifndef PADDLE_H
#define PADDLE_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

struct paddleIntent {
  bool moveUp;
  bool moveDown;
};

struct paddleBindings {
  SDL_Keycode up;
  SDL_Keycode down;
};

struct paddle {
  float mPosX, mPosY, mWidth, mHeight, speed;
  SDL_Keycode mUpButton, mDownButton;
  bool mUp, mDown;
  SDL_FRect mPaddle;
  paddle(float, float);
  ~paddle();
  void update(paddleIntent, int, float);
  void render(SDL_Renderer*);
};

#endif
