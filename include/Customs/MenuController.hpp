#ifndef __MENU_CONTROLLER__
#define __MENU_CONTROLLER__

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
