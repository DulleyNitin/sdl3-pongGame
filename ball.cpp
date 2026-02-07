#include "ball.h"
#include "paddle.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
//#include <algorithm>
//#include <cstdlib>

Ball::Ball() {
  mBallSize = 15.f; 
  mVelX = 600.f; //pixels per second with implementation of delta time (dt)
  mVelY = 600.f;
  mPosX = 485.f;
  mPosY = 275.f;
  mBall = {mPosX, mPosY, mBallSize, mBallSize};
}

Ball::~Ball() {

}

BallResult Ball::update(paddle pad1, paddle pad2, int worldHeight, int worldWidth, float dt) {
  BallResult ballResult = BallResult::none; //yeah i should have better naming 
  //update the balls position with its velocity
  mBall.x += mVelX * dt;
  mBall.y += mVelY * dt;

  //check if ball went out of bounds
  //if ball hit the top and bottom of the screen
  if(mBall.y <=0 || mBall.y+mBall.h >= worldHeight) {
    mVelY = -mVelY;
  }

  //if ball goes out from left or right side of the screen set it back to center
  if(mBall.x <=0) {
    mBall.x = mPosX;
    mBall.y = mPosY;
    ballResult = BallResult::ballLeftOut;
  }
  else if(mBall.x >= worldWidth) {
    mBall.x = mPosX;
    mBall.y = mPosX;
    ballResult = BallResult::ballRightOut;
  }

  if(collisionDetection(pad1.mPaddle, mBall)){ //if ball and paddle(pad1) collided
    calculatVelocity(reposition(pad1.mPaddle));
  }
  if(collisionDetection(pad2.mPaddle, mBall)){ //if ball and paddle(pad2) collided
    calculatVelocity(reposition(pad2.mPaddle));
  }
  return ballResult;
}

void Ball::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer ,255 ,251 ,240, 255);
  SDL_RenderRect(renderer, &mBall);
  SDL_RenderFillRect(renderer, &mBall);
}

int Ball::reposition(SDL_FRect pad) {
  float ballCenterX = mBall.x + mBall.w/2;
  float ballCenterY = mBall.y + mBall.h/2;
  float padCenterX = pad.x + pad.w/2;
  float padCenterY = pad.y + pad.h/2;
  if(overlapY <= overlapX) {
    //check if ball has hit the paddle from bottom or top
    if(ballCenterY < padCenterY) { //if the ball has hit from top
      mBall.y = pad.y-mBall.h;
      return 1;
    }
    if(ballCenterY > padCenterY) {  //if the ball has hit from bottom
      mBall.y = pad.y+pad.h;
      return 2;
    }
  }
  if(overlapX < overlapY) {
    //check if the hit was from the right side or the left side
    if(ballCenterX > padCenterX) { //from right
      mBall.x = pad.x+pad.w;
      return 3;
    }
    if(ballCenterX < padCenterX) { //from left
      mBall.x = pad.x-mBall.w;
      return 4;
    }
  }
  return 0;
}

void Ball::calculatVelocity(int n) {
  switch (n) {
    case 1: // when the ball hits the paddle from top
            // change the velocity only if it makes sense like there is chance that this conditions
            // activates when ball was going up in high speed
      if(mVelY >= 0) {
        mVelY = -mVelY;
      }
      break;
    case 2: //when the ball hits the paddle from bottom
      if(mVelY <= 0) {
        mVelY = -mVelY;
      }
      break;
    case 3://when the ball hits the paddle from right
      if(mVelX <= 0) {
        mVelX = -mVelX;
      }
      break;
    case 4: //when the ball hits the paddle from left
      if(mVelX >= 0) {
        mVelX = -mVelX;
      }
      break;
    }
}

bool Ball::collisionDetection(SDL_FRect box1, SDL_FRect box2) {
  //calculate corner conditions
  //for box1
  point box1TopLeft = {box1.x, box1.y};
  //point box1TopRight = {box1.x+box1.w, box1.y};
  //point box1BottomLeft = {box1.x, box1.y+box1.h};
  point box1BottomRight = {box1.x+box1.w, box1.y+box1.h};
  
  //for box2
  point box2TopLeft = {box2.x, box2.y};
  //point box2TopRight = {box2.x+box2.w, box2.y};
  //point box2BottomLeft = {box2.x, box2.y+box2.h};
  point box2BottomRight = {box2.x+box2.w, box2.y+box2.h};

  if( //make sure to use only two horizontal points for both boxes (like topRight-bottomLeft or topLeft-bottomRight)
      box2TopLeft.x <= box1BottomRight.x 
      && box2BottomRight.x >= box1TopLeft.x 
      && box2BottomRight.y >= box1TopLeft.y
      && box2TopLeft.y <= box1BottomRight.y
    ) {
    overlapX = std::min((box2BottomRight.x - box1TopLeft.x), (box1BottomRight.x - box2TopLeft.x));
    overlapY = std::min((box2BottomRight.y - box1TopLeft.y), (box1BottomRight.y - box2TopLeft.y));
    return true;
  } else {
    return false;
  }
}

