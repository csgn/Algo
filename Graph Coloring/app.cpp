#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

SDL_Rect *
createRect(const Uint32 x, const Uint32 y,
           const Uint32 w, const Uint32 h,
           std::vector<SDL_Rect> &objects)
{
  SDL_Rect *r = new SDL_Rect();
  r->x = x;
  r->y = y;
  r->w = w;
  r->h = h;

  objects.push_back(*r);

  return r;
}

void drawObjects(
    SDL_Window *window,
    SDL_Renderer *renderer,
    std::vector<SDL_Rect> &objects)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  for (SDL_Rect &object : objects)
    SDL_RenderFillRect(renderer, &object);

  SDL_RenderPresent(renderer);
}

int start(SDL_Window *window)
{
  std::vector<SDL_Rect> objects;

  SDL_bool running = SDL_TRUE;
  SDL_Event event;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  while (running)
  {
    while (SDL_PollEvent(&event) > 0)
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running = SDL_FALSE;
        break;
      }

      drawObjects(window, renderer, objects);
    }
  }

  return 0;
}

int stop(SDL_Window *window)
{
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

int main(int argc, char const *argv[])
{
  std::string title = "DEMO";
  const int x = 0, y = 0, w = 800, h = 600;

  SDL_Window *window;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to initialize the SDL2: " << SDL_GetError();
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      w, h, SDL_WINDOW_OPENGL);

  if (window == nullptr)
  {
    std::cout << "Could not create window: " << SDL_GetError();
    return EXIT_FAILURE;
  }

  start(window);
  stop(window);

  return EXIT_SUCCESS;
}
