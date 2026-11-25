#pragma once

#include <memory>
#include <string>

#include <App/Window.h>

namespace Flat
{
class App
{
private:
  bool m_Running = true;

  std::unique_ptr<FWindow> m_Window;

private:
  bool Initialize(std::string appName, int windowW, int windowH);

public:
  App(std::string appName, int windowW, int windowH);
  ~App();

  void Run();
  void Quit();
};
} // namespace Flat
