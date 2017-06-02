#include "Customs/MenuController.h"

MenuController *MenuController::m_instance = nullptr;

MenuController::MenuController() {}

MenuController *MenuController::GetInstance() {
  if (!m_instance)
    m_instance = new MenuController();
  return m_instance;
}

void MenuController::SelectGamemode(char gamemode) {
  m_selectedGamemode = gamemode;
}

char MenuController::GetGamemode() { return m_selectedGamemode; }
