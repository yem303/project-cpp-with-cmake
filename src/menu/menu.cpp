#include "menu/Menu.hpp"
#include "auth/Auth.hpp"
#include "auth/User.hpp"
#include "auth/Admin.hpp"
#include "products/ProductManager.hpp"

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

// ================= COLORS =================
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// ================= Print Menu =================
void Menu::printMenu(const vector<string>& items, const string& title) {
    tabulate::Table table;
    table.add_row({"No", title});
    table[0].format()
        .font_color(tabulate::Color::yellow)
        .font_style({tabulate::FontStyle::bold});

    for (size_t i = 0; i < items.size(); i++) {
        table.add_row({to_string(i + 1), items[i]});
    }

    cout << table << endl;
}

// ================= login banner =================
static void showSecureLoginBanner(const string& role) {
    string label = (role == "admin") ? "✓ Administrator Access ✓" : "         ✓ User Access ✓";

    cout << CYAN;
    cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "    ║                        SECURE LOGIN                           ║\n";
    cout << "    ╠═══════════════════════════════════════════════════════════════╣\n";
    cout << "    ║                                                               ║\n";
    cout << "    ║                   " << YELLOW << label << CYAN << "                    ║\n";
    cout << "    ║                                                               ║\n";
    cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";
    cout << RESET;
}

// ================= LOGIN SUCCESS ANIMATION =================
static void showLoginSuccess() {
    cout << GREEN << "\n    Authenticating...\n";
    cout << "    Loading: [";
    for (int i = 0; i <= 30; i++) {
        cout << GREEN << "█";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(40));
    }
    cout << "] 100%\n" << RESET;

    cout << GREEN;
    cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "    ║              ✓✓  Login Successful!  ✓✓                        ║\n";
    cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";
    cout << RESET;

    this_thread::sleep_for(chrono::milliseconds(800));
}

// ================= LOADING =================
void Menu::loadingText() {
    cout << CYAN << "    Loading...\n\n";

    // Combined ASCII to ensure alignment
    cout << BLUE << R"(        ██╗███████╗████████╗ █████╗ ██████╗ )" << RED << "       " << WHITE << R"( ██████╗ ██████╗ )" << "\n";
    cout << BLUE << R"(        ██║██╔════╝╚══██╔══╝██╔══██╗██╔══██╗)" << RED << "       " << WHITE << R"(██╔════╝ ╚════██╗)" << "\n";
    cout << BLUE << R"(        ██║███████╗   ██║   ███████║██║  ██║)" << RED << "██████╗" << WHITE << R"(██║  ███╗ █████╔╝)" << "\n";
    cout << BLUE << R"(        ██║╚════██║   ██║   ██╔══██║██║  ██║)" << RED << "╚═════╝" << WHITE << R"(██║   ██║██╔═══╝ )" << "\n";
    cout << BLUE << R"(        ██║███████║   ██║   ██║  ██║██████╔╝)" << RED << "       " << WHITE << R"(╚██████╔╝███████╗)" << "\n";
    cout << BLUE << R"(        ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═════╝ )" << RED << "      " << WHITE << R"( ╚═════╝ ╚══════╝)" << "\n";

    cout << RESET << "\n\n";

    const int barWidth = 50;
    cout << GREEN << "    [";
    
    for (int i = 0; i <= barWidth; i++) {
        float progress = (float)i / barWidth;
        int pos = barWidth * progress;

        cout << GREEN << "█"; // Using a solid block
        cout.flush();
        
        this_thread::sleep_for(chrono::milliseconds(40));
    }
    
    cout << "] 100%" << RESET << "\n";
    cout << GREEN << "\n    ✓ System Ready!\n" << RESET;
    this_thread::sleep_for(chrono::seconds(1));
}

// ================= MAIN MENU =================
void Menu::showMainMenu() {
    cout << CYAN << BOLD;
    cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "    ║              PRODUCTS  MANAGEMENT SYSTEM 2026                 ║\n";
    cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << CYAN;
    cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "    ║                         MAIN MENU                             ║\n";
    cout << "    ╠═══════════════════════════════════════════════════════════════╣\n";
    cout << "    ║                                                               ║\n";
    cout << "    ║  " << YELLOW << "[1]  >>  Administrator Access" << CYAN << "                                ║\n";
    cout << "    ║       └─ Manage products, inventory, and system settings      ║\n";
    cout << "    ║                                                               ║\n";
    cout << "    ║  " << MAGENTA << "[2]  >>  User Portal" << CYAN << "                                         ║\n";
    cout << "    ║       └─ Show products and search products                    ║\n";
    cout << "    ║                                                               ║\n";
    cout << "    ║  " << RED << "[3]  >>  Exit Application" << CYAN << "                                    ║\n";
    cout << "    ║       └─ Save and close the system                            ║\n";
    cout << "    ║                                                               ║\n";
    cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";

    cout << GREEN;
    cout << "\n    ┌───────────────────────────────────────────────────────────────┐\n";
    cout << "    │        Select an option by entering the number (1-3)          │\n";
    cout << "    └───────────────────────────────────────────────────────────────┘\n";
    cout << RESET;

    cout << MAGENTA << "\n    Enter your choice > " << RESET;
}

// ================= AUTH MENU =================
void Menu::authMenu() {
    Auth auth;
    auth.initFile();

    User currentUser;
    bool loggedIn = false;
    int choice;

    while (true) {
        showMainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "    ✗ Invalid input!\n" << RESET;
            continue;
        }

        if (choice == 3) {
            cout << GREEN << "\n    Saving and exiting...\n" << RESET;
            exit(0);
        }

        if (choice == 1 || choice == 2) {
            string roleHint = (choice == 1) ? "admin" : "user";
            showSecureLoginBanner(roleHint);
            
            // Show login/register 
            cout << CYAN << "    ╔═══════════════════════════════════════════════════════════════╗\n";
            cout << "    ║                        LOGIN / REGISTER                       ║\n";
            cout << "    ╠═══════════════════════════════════════════════════════════════╣\n";
            cout << "    ║                                                               ║\n";
            cout << "    ║  " << GREEN << "             [1]  Login" << CYAN << "                                      ║\n";
            cout << "    ║  " << BLUE << "             [2]  Register New Account" << CYAN << "                       ║\n";
            cout << "    ║  " << RED << "             [3]  Back to Main Menu" << CYAN << "                          ║\n";
            cout << "    ║                                                               ║\n";
            cout << "    ╚═══════════════════════════════════════════════════════════════╝\n" << RESET;
            
            cout << MAGENTA << "\n    Enter your choice > " << RESET;
            
            int authChoice;
            if (!(cin >> authChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << RED << "    ✗ Invalid input!\n" << RESET;
                continue;
            }
            
            if (authChoice == 1) {
                // Login
                loggedIn = auth.login(currentUser);
                if (loggedIn) {
                    // Check if user role matches selected portal
                    if ((choice == 1 && currentUser.getRole() == "admin") ||
                        (choice == 2 && currentUser.getRole() == "user")) {
                        showLoginSuccess();
                        break;
                    } else {
                        cout << RED << "\n    ✗ Access denied! Wrong portal for this account type.\n" << RESET;
                        this_thread::sleep_for(chrono::milliseconds(1500));
                    }
                }
            } 
            else if (authChoice == 2) {
                // Register
                cout << CYAN << "\n    ╔════════════════════════════════════════════════════════════════╗\n";
                cout << "    ║                       REGISTER NEW ACCOUNT                     ║\n";
                cout << "    ╚════════════════════════════════════════════════════════════════╝\n" << RESET;
                
                auth.registerUser(); // This will handle the registration UI
                
                cout << GREEN << "\n    ✓ Registration successful! Please login.\n" << RESET;
                this_thread::sleep_for(chrono::milliseconds(1500));
                
                
                loggedIn = auth.login(currentUser);
                if (loggedIn) {
                    if ((choice == 1 && currentUser.getRole() == "admin") ||
                        (choice == 2 && currentUser.getRole() == "user")) {
                        showLoginSuccess();
                        break;
                    }
                }
            }
            else if (authChoice == 3) {
                continue; // Back to main menu
            }
            else {
                cout << RED << "    ✗ Invalid choice!\n" << RESET;
            }
        } else {
            cout << RED << "    ✗ Invalid choice!\n" << RESET;
        }
    }

    ProductManager manager;
    vector<Product> productList;
    
    try {
        manager.loadFromExcel("products.xlsx", productList);
    } catch (...) {
        cout << YELLOW << "    ⚠ No products file found, starting fresh.\n" << RESET;
    }

    
    cout << "DEBUG role: [" << currentUser.getRole() << "]\n";
    cout << "DEBUG username: [" << currentUser.getUsername() << "]\n";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    if (currentUser.getRole() == "admin") {
        adminMenu(manager);
    } else if (currentUser.getRole() == "user") {
        userMenu(manager, currentUser);
    } else {
        cout << RED << "    ✗ ERROR: Role is empty or unknown: [" 
             << currentUser.getRole() << "]\n" << RESET;
        cin.get();
    }

    manager.writeProductToexcel("products.xlsx", productList);
}
// ================= ADMIN MENU =================
void Menu::adminMenu(ProductManager& manager) {
    int option;

    do {
        cout << CYAN;
        cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
        cout << "    ║                      MANAGEMENT MENU                          ║\n";
        cout << "    ╠═══════════════════════════════════════════════════════════════╣\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[1]  ➕  Add New Product" << CYAN << "                                     ║\n";
        cout << "    ║       └─ Add completely new products to inventory             ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[2]  📦  Stock In" << CYAN << "                                            ║\n";
        cout << "    ║       └─ Increase quantity of existing products               ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[3]  📤  Stock Out" << CYAN << "                                           ║\n";
        cout << "    ║       └─ Decrease quantity of existing products               ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[4]  🪟  View Product Inventory" << CYAN << "                               ║\n";
        cout << "    ║       └─ Display all current products                         ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[5]  ✏️  Update Product Details" << CYAN << "                               ║\n";
        cout << "    ║       └─ Modify existing product information                  ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[6]  🗑️  Remove Product" << CYAN << "                                       ║\n";
        cout << "    ║       └─ Delete items from inventory                          ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[7]  📊  Sort Products" << CYAN << "                                       ║\n";
        cout << "    ║       └─ Sort products by name, price, or quantity            ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[8]  ⚠️  Stock Alert" << CYAN << "                                          ║\n";
        cout << "    ║       └─ View low stock products and set thresholds           ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[9]  🚪  Exit Program" << CYAN << "                                        ║\n";
        cout << "    ║       └─ Exit administrator panel                             ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";
        cout << RESET;

        cout << GREEN;
        cout << "\n    ┌───────────────────────────────────────────────────────────────┐\n";
        cout << "    │     Select an option to manage inventory (1-9)                │\n";
        cout << "    └───────────────────────────────────────────────────────────────┘\n";
        cout << RESET;

        cout << MAGENTA << "\n    Enter your choice > " << RESET;

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "    ✗ Invalid input!\n" << RESET;
            continue;
        }

        switch (option) {
            case 1: {
            cout << "\n";
            manager.addProduct();
            break;
        }

        case 2: {
            manager.stockIn();
            break;
        }

        case 3: {
            manager.stockOut();
            break;
        }

        case 4: {
            cout << "\n";
            manager.showProducts();
            break;
        }

        case 5: {
            cout << "\n";
            manager.updateProduct();
            break;
        }

        case 6: {
            cout << "\n";
            manager.deleteProduct();
            break;
        }

        case 7: {
            cout << "\n";
            manager.sortProducts();
            break;
        }

        case 8: {
            manager.stockAlert();
            break;
        }

        case 9:
            cout << GREEN
                << "\n    🔙 Returning to main menu...\n"
                << RESET;
            break;

        default:
            cout << RED
                << "    ❌ Invalid choice! Please select 1-9\n"
                << RESET;
                
                if (option != 6 && option >= 1 && option <= 4) {
                    cout << "\n    Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
        }

    } while (option != 9);
}

// ================= USER MENU =================
void Menu::userMenu(ProductManager& manager, const User& user) {
    int option;

    cout << GREEN << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "    ║                    Welcome, " << user.getUsername() 
        << " (" << user.getRole() << ")" << string(43 - user.getUsername().length() - user.getRole().length() - 12, ' ') << "║\n";
    cout << "    ╚═══════════════════════════════════════════════════════════════╝\n" << RESET;

    do {
        cout << CYAN;
        cout << "\n    ╔═══════════════════════════════════════════════════════════════╗\n";
        cout << "    ║                           🛒 USER PANEL 🛒                    ║\n";
        cout << "    ╠═══════════════════════════════════════════════════════════════╣\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[1]  🪟  Show Products" << CYAN << "                                        ║\n";
        cout << "    ║       └─ Browse available inventory                           ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[2]  🔍  Search Product" << CYAN << "                                      ║\n";
        cout << "    ║       └─ Find a specific product                              ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ║  " << MAGENTA << "[3]  ⬅️  Exit" << CYAN << "                                                 ║\n";
        cout << "    ║       └─ Return to main menu                                  ║\n";
        cout << "    ║                                                               ║\n";
        cout << "    ╚═══════════════════════════════════════════════════════════════╝\n";

        cout << GREEN;
        cout << "\n    ┌───────────────────────────────────────────────────────────────┐\n";
        cout << "    │        Select an option by entering the number (1-3)          │\n";
        cout << "    └───────────────────────────────────────────────────────────────┘\n";
        cout << RESET;

        cout << MAGENTA << "\n    Enter your choice > " << RESET;

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "    ✗ Invalid input!\n" << RESET;
            continue;
        }
        switch (option) {
            case 1: 
                cout << "\n";
                manager.showProducts(); 
                break;
            case 2: 
                cout << "\n";
                manager.searchProduct(); 
                break;
            case 3: 
                cout << GREEN << "\n    Exiting user menu...\n" << RESET; 
                break;
            default: 
                cout << RED << "    ✗ Invalid choice!\n" << RESET;
        }
        
        if (option != 3 && option >= 1 && option <= 2) {
            cout << "\n    Press Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (option != 3);
}