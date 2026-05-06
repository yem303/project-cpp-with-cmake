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
    Sleep(800);
    
    system("cls");
    menu.authMenu();
    
    // Clean exit message
    cout << "\n    Thank you for using ISTAD Inventory System!\n";
    cout << "    Goodbye!\n\n";
    
    
    return 0;
}