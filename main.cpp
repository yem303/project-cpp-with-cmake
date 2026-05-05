#include <windows.h>
#include "menu/Menu.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    Menu menu;
    menu.authMenu();   

    return 0;
}