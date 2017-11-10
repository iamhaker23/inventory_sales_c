/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Inventory.h
 * Author: Hakeem
 *
 * Created on 03 November 2017, 12:08
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
    
    typedef struct _INode{
        StockItem* item;
        struct _INode* next;
        struct _INode* previous;
    } INode;

    typedef struct _Inventory{
        INode* first;
        int length;
        INode* last;
    } Inventory;
   
    //load from file
    void load_inventory(FILE* fd, Inventory* inventory);
    
    //Will add item and store pointer
    void inventory_add(Inventory* inventory, StockItem* item);
    
    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code);
    
    //helps determine total stock level of NPN transistors
    int count_type_matching_description_in_stock(Inventory* inventory, char* type, char* description);
    
    float total_resistance_of_in_stock_resistors(Inventory* inventory);
    
    Inventory* get_subset_of_in_stock(Inventory* inventory, char* type, char* description);

    Inventory* inventory_new();

    void inventory_as_string(Inventory* list, char *tmp, int tmp_length);
    
    void inventory_as_csv(Inventory* inventory, char* tmp, int tmp_length);
    
    int inventory_length(Inventory* list);

    void inventory_empty(Inventory* list);

    void inventory_sort(Inventory* list, int ascending_flag);

    void inventory_gc(Inventory* list);

    int inventory_estimate_required_buffer(Inventory* list);


#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */

