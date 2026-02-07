#include "UImanager.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <string>

UImanager::UImanager() {
  if(!TTF_Init()) { //initialize TTF_Init
    SDL_Log("failed to initialize SDL_TTF");
  }
  mFontSize = 80;
  mColor = {255, 255, 255, SDL_ALPHA_OPAQUE};
  mScore1Pos = {435, 5, 20, 40};
  mScore2Pos = {495, 5, 20, 40};
  mFpsPos = {465, 500, 40, 40};
  mFont = TTF_OpenFont("./assets/Pixellettersfull-BnJ5.ttf", mFontSize);
  if(!mFont) {
    SDL_Log("unable to load the font");
  }
}

UImanager::~UImanager() {
  if(mFont) {
    TTF_CloseFont(mFont);
  }
  TTF_Quit();
}

void UImanager::render(SDL_Renderer* renderer, int score1, int score2, int fps) {
  SDL_Surface *textSurface; // will be reusing this for scores and fps

  //for score 1
  mText = std::to_string(score1); 
  textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), 0, mColor);
  mScore1Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

  mText = std::to_string(score2); 
  textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), 0, mColor);
  mScore2Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

  //for score 2
  mText = std::to_string(fps);
  textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), 0, mColor);
  mFpsTexture = SDL_CreateTextureFromSurface(renderer, textSurface);


  SDL_RenderTexture(renderer, mScore1Texture, NULL, &mScore1Pos);
  SDL_RenderTexture(renderer, mScore2Texture, NULL, &mScore2Pos);
  SDL_RenderTexture(renderer, mFpsTexture, NULL, &mFpsPos);


  SDL_DestroySurface(textSurface);

}

