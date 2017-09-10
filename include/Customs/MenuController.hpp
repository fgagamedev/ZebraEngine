#ifndef __MENU_CONTROLLER__
#define __MENU_CONTROLLER__

/**
    @file MenuController.hpp
    @brief Class that defines methods and attributes for build and use the game menu.
    @copyright LGPL. MIT License.
*/

class MenuController {
public:
    static MenuController *GetInstance();
    void SelectGamemode(char gamemode);
    char GetGamemode();

private:
    MenuController();
    static MenuController *m_instance;
    char m_selectedGamemode = 0x02;
};

#endif
