#include <windows.h>
#include <iostream>
#include "menu/Menu.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(TEXT("ISTAD Inventory Management System - G2"));
    // Clear screen
    system("cls");
    Menu menu;
    
    menu.loadingText();
    Sleep(1000);
    
    system("cls");
    menu.authMenu();
    
    
    return 0;
}