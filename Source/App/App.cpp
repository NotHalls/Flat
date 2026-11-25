#include <FlatPCH.h>

#include "SDL3/SDL_events.h"

#include "App.h"
#include "App/Window.h"
#include "SDL3/SDL_init.h"

namespace Flat
{
App::App(std::string appName, int windowW, int windowH)
{
  F_ASSERT(Initialize(appName, windowW, windowH),
           "Failed To Initialize Application");
}
App::~App() {}

bool App::Initialize(std::string appName, int windowW, int windowH)
{
  m_Window = std::make_unique<FWindow>(appName, windowW, windowH);
  return true;
}

void App::Run()
{
  while(m_Running)
  {
    SDL_Event event{0};
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
      case SDL_EVENT_QUIT:
        m_Running = false;
        break;

      case SDL_EVENT_WINDOW_RESIZED:
        m_Window->Resize(event.window.data1, event.window.data2);
        break;
      }
    }
  }
}

void App::Quit()
{
  FLog("Quiting Application...");
  SDL_Quit();
}
} // namespace Flat
