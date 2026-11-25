#include <FlatPCH.h>

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"

#include "Window.h"

namespace Flat
{
FWindow::FWindow(std::string windowName, int width, int height)
    : m_WindowName(windowName), m_Width(width), m_Height(height)
{
  m_Window = nullptr;

  F_ASSERT(Initialize(), "Failed To Create FWindow");
  FLog("Successfully Created An FWindow!");
}

FWindow::~FWindow() { SDL_DestroyWindow(m_Window); }

bool FWindow::Initialize()
{
  FLog("Creating Window...");

  if(!SDL_InitSubSystem(SDL_INIT_VIDEO))
  {
    FLogError("Failed To Initialize SDL_Video \nCause: " +
              std::string(SDL_GetError()));
    return false;
  }

  m_Window = SDL_CreateWindow(m_WindowName.c_str(), m_Width, m_Height,
                              SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
  if(!m_Window)
  {
    FLogError("Failed To Create SDL_Window \nCause: " +
              std::string(SDL_GetError()));
    return false;
  }

  return true;
}

void FWindow::Resize(int w, int h)
{
  m_Width = w;
  m_Height = h;
}
} // namespace Flat
