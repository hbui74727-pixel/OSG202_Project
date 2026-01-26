#ifndef INVENTORY_H
#define INVENTORY_H
typedef struct {  // 1 ô trong túi 
    int item_id;
    int quantity;
}ItemStack;
typedef struct{ // túi đồ chứ các ô 
    ItemStack* items;
    int count;
    int capacity;

}Inventory;
int init_inventory(Inventory* inv, int capaccity);
int add_item(Inventory* inv,int item_id,int quantity);
void free_inventory(Inventory* inv);
#endif