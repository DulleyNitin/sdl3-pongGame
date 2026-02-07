#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

struct UImanager {
  int mFontSize;
  std::string mText;
  SDL_Color mColor;
  TTF_Font *mFont = nullptr;
  SDL_Texture *mScore1Texture = nullptr;
  SDL_Texture *mScore2Texture = nullptr;
  SDL_Texture *mFpsTexture = nullptr;
  SDL_FRect mScore1Pos, mScore2Pos, mFpsPos;
  UImanager();
  ~UImanager();
  void render(SDL_Renderer*, int, int, int);
};

#endif // !UI_MANAGER_H

