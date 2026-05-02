#ifndef INVENTORY_H
#define INVENTORY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    int is_deleted;  // 0 = active, 1 = deleted (soft delete)
} Item;

// C functions for inventory management
int add_item(Item item);
int get_item(int id, Item* item);
int update_item(Item item);
int delete_item(int id);
int list_items(Item** items, int* count);
int get_next_id();

#ifdef __cplusplus
}
#endif

#endif // INVENTORY_H
