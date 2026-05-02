#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <cstring>
#include "../include/inventory.h"

class InventoryManager {
private:
    std::vector<Item> items;
    
    // Load items from file into vector
    void loadItems() {
        items.clear();
        Item* itemArray = nullptr;
        int count = 0;
        
        if (list_items(&itemArray, &count)) {
            for (int i = 0; i < count; i++) {
                items.push_back(itemArray[i]);
            }
            if (itemArray != nullptr) {
                free(itemArray);
            }
        }
    }
    
    // Sort items by ID
    void sortItems() {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.id < b.id;
        });
    }
    
public:
    // Add a new item
    bool addItem() {
        Item item;
        item.id = get_next_id();
        
        std::cout << "\n=== Add New Item ===\n";
        std::cout << "Item ID: " << item.id << " (auto-generated)\n";
        
        std::cout << "Enter item name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(item.name, 50);
        
        // Validate name
        if (strlen(item.name) == 0) {
            std::cout << "Error: Item name cannot be empty!\n";
            return false;
        }
        
        std::cout << "Enter quantity: ";
        while (!(std::cin >> item.quantity) || item.quantity < 0) {
            std::cout << "Error: Please enter a valid non-negative quantity: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "Enter price: ";
        while (!(std::cin >> item.price) || item.price < 0) {
            std::cout << "Error: Please enter a valid non-negative price: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        if (add_item(item)) {
            std::cout << "\nItem added successfully!\n";
            return true;
        } else {
            std::cout << "\nError: Failed to add item!\n";
            return false;
        }
    }
    
    // View an item by ID
    bool viewItem() {
        int id;
        std::cout << "\n=== View Item ===\n";
        std::cout << "Enter item ID: ";
        
        while (!(std::cin >> id) || id <= 0) {
            std::cout << "Error: Please enter a valid positive ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        Item item;
        if (get_item(id, &item)) {
            std::cout << "\n--- Item Details ---\n";
            std::cout << "ID:       " << item.id << "\n";
            std::cout << "Name:     " << item.name << "\n";
            std::cout << "Quantity: " << item.quantity << "\n";
            std::cout << "Price:    $" << item.price << "\n";
            return true;
        } else {
            std::cout << "\nError: Item not found!\n";
            return false;
        }
    }
    
    // Update an existing item
    bool updateItem() {
        int id;
        std::cout << "\n=== Update Item ===\n";
        std::cout << "Enter item ID to update: ";
        
        while (!(std::cin >> id) || id <= 0) {
            std::cout << "Error: Please enter a valid positive ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        Item item;
        if (!get_item(id, &item)) {
            std::cout << "\nError: Item not found!\n";
            return false;
        }
        
        std::cout << "\nCurrent details:\n";
        std::cout << "Name:     " << item.name << "\n";
        std::cout << "Quantity: " << item.quantity << "\n";
        std::cout << "Price:    $" << item.price << "\n";
        
        std::cout << "\nEnter new item name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(item.name, 50);
        
        if (strlen(item.name) == 0) {
            std::cout << "Error: Item name cannot be empty!\n";
            return false;
        }
        
        std::cout << "Enter new quantity: ";
        while (!(std::cin >> item.quantity) || item.quantity < 0) {
            std::cout << "Error: Please enter a valid non-negative quantity: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "Enter new price: ";
        while (!(std::cin >> item.price) || item.price < 0) {
            std::cout << "Error: Please enter a valid non-negative price: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        if (update_item(item)) {
            std::cout << "\nItem updated successfully!\n";
            return true;
        } else {
            std::cout << "\nError: Failed to update item!\n";
            return false;
        }
    }
    
    // Delete an item (soft delete)
    bool deleteItem() {
        int id;
        std::cout << "\n=== Delete Item ===\n";
        std::cout << "Enter item ID to delete: ";
        
        while (!(std::cin >> id) || id <= 0) {
            std::cout << "Error: Please enter a valid positive ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        Item item;
        if (!get_item(id, &item)) {
            std::cout << "\nError: Item not found!\n";
            return false;
        }
        
        std::cout << "\nItem to delete:\n";
        std::cout << "ID:   " << item.id << "\n";
        std::cout << "Name: " << item.name << "\n";
        
        char confirm;
        std::cout << "\nAre you sure you want to delete this item? (y/n): ";
        std::cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            if (delete_item(id)) {
                std::cout << "\nItem deleted successfully!\n";
                return true;
            } else {
                std::cout << "\nError: Failed to delete item!\n";
                return false;
            }
        } else {
            std::cout << "\nDeletion cancelled.\n";
            return false;
        }
    }
    
    // List all items (sorted)
    void listAllItems() {
        std::cout << "\n=== All Items ===\n";
        
        loadItems();
        
        if (items.empty()) {
            std::cout << "No items in inventory.\n";
            return;
        }
        
        sortItems();
        
        std::cout << "\n";
        std::cout << "ID\tName\t\t\tQuantity\tPrice\n";
        std::cout << "-----------------------------------------------------------\n";
        
        for (const auto& item : items) {
            std::cout << item.id << "\t";
            std::cout << item.name;
            
            // Add padding for alignment
            int nameLen = strlen(item.name);
            if (nameLen < 16) {
                for (int i = 0; i < (16 - nameLen); i++) {
                    std::cout << " ";
                }
            }
            
            std::cout << "\t" << item.quantity << "\t\t$" << item.price << "\n";
        }
        
        std::cout << "\nTotal items: " << items.size() << "\n";
    }
};

// Global instance for use in main.cpp
InventoryManager manager;

// Wrapper functions for C++ class methods
extern "C" {
    void cpp_add_item() { manager.addItem(); }
    void cpp_view_item() { manager.viewItem(); }
    void cpp_update_item() { manager.updateItem(); }
    void cpp_delete_item() { manager.deleteItem(); }
    void cpp_list_items() { manager.listAllItems(); }
}
