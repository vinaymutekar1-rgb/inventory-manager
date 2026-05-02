#include <iostream>
#include <limits>
#include "../include/inventory.h"

// External C++ wrapper functions
extern "C" {
    void cpp_add_item();
    void cpp_view_item();
    void cpp_update_item();
    void cpp_delete_item();
    void cpp_list_items();
}

void displayMenu() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "    HYBRID INVENTORY MANAGER\n";
    std::cout << "========================================\n";
    std::cout << "1. Add Item\n";
    std::cout << "2. View Item\n";
    std::cout << "3. Update Item\n";
    std::cout << "4. Delete Item\n";
    std::cout << "5. List All Items\n";
    std::cout << "6. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice (1-6): ";
}

int main() {
    int choice;
    bool running = true;
    
    std::cout << "\n";
    std::cout << "****************************************\n";
    std::cout << "  Welcome to Hybrid Inventory Manager  \n";
    std::cout << "****************************************\n";
    std::cout << "  C Backend + C++ Frontend Solution    \n";
    std::cout << "****************************************\n";
    
    while (running) {
        displayMenu();
        
        // Input validation for menu choice
        while (!(std::cin >> choice) || choice < 1 || choice > 6) {
            std::cout << "Invalid input! Please enter a number between 1 and 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        switch (choice) {
            case 1:
                cpp_add_item();
                break;
            case 2:
                cpp_view_item();
                break;
            case 3:
                cpp_update_item();
                break;
            case 4:
                cpp_delete_item();
                break;
            case 5:
                cpp_list_items();
                break;
            case 6:
                std::cout << "\n";
                std::cout << "========================================\n";
                std::cout << "  Thank you for using Inventory Manager!\n";
                std::cout << "========================================\n";
                running = false;
                break;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
        }
        
        if (running && choice >= 1 && choice <= 5) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    return 0;
}
