#include <print>

#include <App/App.h>

int main()
{
  Flat::App app("Flat", 600, 500);

  app.Run();
  app.Quit();
}
