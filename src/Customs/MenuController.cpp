#include "Customs/MenuController.hpp"

/**
    @file MenuController.cpp
    @brief Methods that manages the selections in the game menu.
    @copyright LGPL. MIT License.
*/

MenuController *MenuController::m_instance = nullptr;

// Constructor
MenuController::MenuController() {}

/**
    @brief Receives the input of the new game mode, if there's no previous one.
    @return m_instance of MenuController
*/
MenuController *MenuController::GetInstance() {
  if (!m_instance)
    m_instance = new MenuController();
  return m_instance;
}

/**
    @brief Defines the char entered as the selected game mode.
    @param[in] gamemode - a char that define the selected game mode.
*/
void MenuController::SelectGamemode(char gamemode) {
    m_selectedGamemode = gamemode;
}

/**
    @brief Gets the selected game mode.
    @return char
*/
char MenuController::GetGamemode() { 
    return m_selectedGamemode; 
}
