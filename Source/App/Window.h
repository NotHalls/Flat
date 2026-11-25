#pragma once

#include <string>

struct SDL_Window;

namespace Flat
{
class FWindow
{
private:
  SDL_Window *m_Window;

  std::string m_WindowName;
  int m_Width;
  int m_Height;

private:
  bool Initialize();

public:
  FWindow(std::string windowName, int width, int height);
  ~FWindow();

  void Resize(int w, int h);

  // Getters
  SDL_Window *Get() { return m_Window; }
  int GetWidth() { return m_Width; }
  int GetHeight() { return m_Height; }
};
} // namespace Flat
