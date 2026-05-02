#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inventory.h"

#define FILENAME "inventory.dat"

// Get the next available ID
int get_next_id() {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        return 1;  // First ID
    }
    
    int max_id = 0;
    Item item;
    
    while (fread(&item, sizeof(Item), 1, file) == 1) {
        if (item.id > max_id) {
            max_id = item.id;
        }
    }
    
    fclose(file);
    return max_id + 1;
}

// Add a new item to the inventory
int add_item(Item item) {
    FILE* file = fopen(FILENAME, "ab");
    if (file == NULL) {
        return 0;  // Failure
    }
    
    item.is_deleted = 0;  // Mark as active
    
    if (fwrite(&item, sizeof(Item), 1, file) != 1) {
        fclose(file);
        return 0;  // Failure
    }
    
    fclose(file);
    return 1;  // Success
}

// Get an item by ID
int get_item(int id, Item* item) {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        return 0;  // Failure
    }
    
    Item temp;
    while (fread(&temp, sizeof(Item), 1, file) == 1) {
        if (temp.id == id && temp.is_deleted == 0) {
            *item = temp;
            fclose(file);
            return 1;  // Success
        }
    }
    
    fclose(file);
    return 0;  // Not found
}

// Update an existing item
int update_item(Item item) {
    FILE* file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        return 0;  // Failure
    }
    
    Item temp;
    long position;
    
    while ((position = ftell(file)), fread(&temp, sizeof(Item), 1, file) == 1) {
        if (temp.id == item.id && temp.is_deleted == 0) {
            // Move back to the position of this record
            fseek(file, position, SEEK_SET);
            item.is_deleted = 0;  // Keep it active
            
            if (fwrite(&item, sizeof(Item), 1, file) != 1) {
                fclose(file);
                return 0;  // Failure
            }
            
            fclose(file);
            return 1;  // Success
        }
    }
    
    fclose(file);
    return 0;  // Not found
}

// Soft delete an item (mark as deleted)
int delete_item(int id) {
    FILE* file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        return 0;  // Failure
    }
    
    Item temp;
    long position;
    
    while ((position = ftell(file)), fread(&temp, sizeof(Item), 1, file) == 1) {
        if (temp.id == id && temp.is_deleted == 0) {
            // Move back to the position of this record
            fseek(file, position, SEEK_SET);
            temp.is_deleted = 1;  // Mark as deleted
            
            if (fwrite(&temp, sizeof(Item), 1, file) != 1) {
                fclose(file);
                return 0;  // Failure
            }
            
            fclose(file);
            return 1;  // Success
        }
    }
    
    fclose(file);
    return 0;  // Not found
}

// List all active (non-deleted) items
int list_items(Item** items, int* count) {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        *items = NULL;
        *count = 0;
        return 1;  // No file yet, return empty list
    }
    
    // Count active items
    Item temp;
    int active_count = 0;
    
    while (fread(&temp, sizeof(Item), 1, file) == 1) {
        if (temp.is_deleted == 0) {
            active_count++;
        }
    }
    
    if (active_count == 0) {
        *items = NULL;
        *count = 0;
        fclose(file);
        return 1;  // Success, but no items
    }
    
    // Allocate memory for items
    *items = (Item*)malloc(sizeof(Item) * active_count);
    if (*items == NULL) {
        fclose(file);
        return 0;  // Memory allocation failure
    }
    
    // Read active items
    fseek(file, 0, SEEK_SET);
    int index = 0;
    
    while (fread(&temp, sizeof(Item), 1, file) == 1) {
        if (temp.is_deleted == 0) {
            (*items)[index++] = temp;
        }
    }
    
    *count = active_count;
    fclose(file);
    return 1;  // Success
}
