#include "Menu.h"

Menu::Menu(){
       hintOption = false;
       pauseOption = false;
       menuControl = 0;
}

void Menu::setHintOption(bool h){
      hintOption = h;
}
bool Menu::getHintOption(){
      return hintOption;
}
void Menu::setPauseOption(bool h){
        pauseOption = h;
}
bool Menu::getPauseOption(){
        return pauseOption;
}
int Menu::getMenuControl(){
        return menuControl;
}
void Menu::setMenuControl(int m){
        menuControl = m;
}
