#include <stdlib.h>
#include "inventory.h"

int init_inventory(Inventory* inv, int capacity) {
    if (inv == NULL || capacity <= 0) {
        return -1;
    }

    inv->items = (ItemStack*)malloc(sizeof(ItemStack) * capacity);
    if (inv->items == NULL) {
        return -1;
    }

    inv->count = 0;
    inv->capacity = capacity;
    return 0;
}
int add_item(Inventory* inv ,int item_id,int quantity){
    if(inv == NULL || quantity <= 0){
        return -1;
    }
    for (int i = 0;i< inv ->count ;i++){
        if (inv->items[i].item_id == item_id) {
            inv->items[i].quantity += quantity;
            return 0;
    }
}
     if (inv->count == inv->capacity) {
        int new_capacity = inv->capacity * 2;
        ItemStack* new_items =
            (ItemStack*)realloc(inv->items, sizeof(ItemStack) * new_capacity);

        if (new_items == NULL) {
            return -1;
        }

        inv->items = new_items;
        inv->capacity = new_capacity;
    }
    inv->items[inv->count].item_id = item_id;
    inv->items[inv->count].quantity = quantity;
    inv->count++;

    return 0;
}
void free_inventory(Inventory* inv) {
    int quantity;
    if (inv != NULL && inv->items != NULL) {
        free(inv->items);
        inv->items = NULL;
        inv->count = 0;
        inv->capacity = 0;
    }

}
