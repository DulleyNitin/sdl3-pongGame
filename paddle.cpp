#include "paddle.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>

paddle::paddle(float x, float y) {
  mUp = false; //states of the paddle i.e going up or down
  mDown = false;
  mPosX = x; //coordinates of the paddle
  mPosY = y;
  mWidth = 20.f; // dimensions of the paddle  for now this must not be changed as i like the dimension right now
  mHeight = 150.f;
  speed = 400.0f; //speed of the paddle in pixels per second with implemention of delta time(dt)
  mPaddle = { mPosX, mPosY, mWidth, mHeight };
}

paddle::~paddle() {

}

void paddle::update(paddleIntent intent, int height, float dt) {
  if(mPosY > 0) { //checking if the paddle stays below the upper limit of the world
    if(intent.moveUp) {
      mPosY -= speed * dt;
    }
  }
  if(mPosY < (height - mHeight)) { //checking if the paddle stays above the lower limit of the world
    if(intent.moveDown) {
      mPosY += speed * dt;
    }
  }
  mPaddle.y = mPosY;
}

void paddle::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer,53 ,79 ,82 ,255); //paddle color
  SDL_RenderRect(renderer, &mPaddle);
  SDL_RenderFillRect(renderer, &mPaddle);
}
