#ifndef BALL_H
#define BALL_H

#include "paddle.h"
#include <cmath>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

enum BallResult {
  none, ballLeftOut, ballRightOut
};

struct point { //to be used in AABB collisionDetection
  float x;
  float y;
};

struct Ball {
  float mVelX, mVelY, mPosX, mPosY, mBallSize;
  float overlapX, overlapY; //this is to implement MTV(minimum translation vector) for now its member variable....
                            //this is calculated during collisionDetection
  SDL_FRect mBall; // contains floating point fields (SDL_Rect is int)
  Ball();
  ~Ball();
  BallResult update(paddle, paddle, int, int, float);
  void render(SDL_Renderer*);
  bool collisionDetection(SDL_FRect, SDL_FRect);
  int reposition(SDL_FRect);
  void calculatVelocity(int);
};

#endif
