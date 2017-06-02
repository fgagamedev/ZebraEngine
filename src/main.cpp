#include "Engine/SDLSystem.h"

int main() {

  SDLSystem::GetInstance()->Init();
  SDLSystem::GetInstance()->Run();
  SDLSystem::GetInstance()->Shutdown();

  return 0;
}
