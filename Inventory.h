/* 
 * File:   Inventory.h
 * Author: Hakeem
 *
 * 
 */

#ifndef INVENTORY_H
#define INVENTORY_H
#include <stdlib.h>
#include <stdio.h>
#include "StockItem.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    //Inventory Node object, creates doubly-linked list
    typedef struct _INode{
        StockItem* item;
        struct _INode* next;
        struct _INode* previous;
    } INode;

    //defines the pointers and length of an Inventory list (doubly linked list)
    typedef struct _Inventory{
        INode* first;
        int length;
        INode* last;
    } Inventory;
   
    //Allocates memory for a new inventory list
    Inventory* inventory_new();
    
    //Returns length of inventory list
    int inventory_length(Inventory* list);
    
    //load from file
    void load_inventory(FILE* fd, Inventory* inventory);
    
    //Will add item to list (store pointer at tail)
    void inventory_add(Inventory* inventory, StockItem* item);
    
    //Return an item given it's product code, if no match return null
    StockItem* get_item_by_product_code(Inventory* inventory, char* code);
    
    //Can count the total number of items given a type and description
    //Used to determine total stock level of NPN transistors
    int count_type_matching_description_in_stock(Inventory* inventory, char* type, char* description);
    
    //Returns aggregate of normalised resistance value of all "resistor" type, where quantity > 0
    float total_resistance_of_in_stock_resistors(Inventory* inventory);
    
    //Returns the subset of stock (as a new inventory list in memory) that matches the type and description (e.g. "transistor", "NPN")
    Inventory* get_subset_of_in_stock(Inventory* inventory, char* type, char* description);

    //populates tmp, up to tmp_length chars, with the inventory in human readable format
    void inventory_as_string(Inventory* list, char *tmp, int tmp_length);
    
    //populates tmp, up to tmp_length chars, with the inventory in CSV format
    void inventory_as_csv(Inventory* inventory, char* tmp, int tmp_length);
    
    //estimate number of bytes required to store given list as string/csv
    int inventory_estimate_required_buffer(Inventory* list);

    //sort the inventory by price, ordering controlled by ascending flag (ascending(1) or descending(0)).
    void inventory_sort(Inventory* list, int ascending_flag);
    
    //empty the inventory list but keep inventory list struct's allocated memory
    void inventory_empty(Inventory* list);

    //remove inventory list and all elements from memory
    void inventory_gc(Inventory* list);


#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */

