#include <windows.h>
#include <iostream>
#include "menu/Menu.hpp"

using namespace std;

int main() {
    // Set console to UTF-8 for proper character display
    SetConsoleOutputCP(CP_UTF8);
    // Set console title
    SetConsoleTitle(TEXT("ISTAD Inventory Management System - G2"));
    // Clear screen
    system("cls");
    // Create menu instance
    Menu menu;
    // Show boot screen with system info
    menu.loadingText();
    // Brief pause to show boot screen
    Sleep(800);
    
    // Clear screen for main menu
    system("cls");
    // Start the main application flow
    // authMenu() will handle:
    // 1. Displaying main menu
    // 2. User/Admin authentication
    // 3. Routing to appropriate panels
    // 4. Auto-save before exit
    menu.authMenu();
    
    // Clean exit message
    cout << "\n    Thank you for using ISTAD Inventory System!\n";
    cout << "    Goodbye!\n\n";
    
    // Pause before exit (optional)
    system("pause");
    
    return 0;
}