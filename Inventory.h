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
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "StockItem.h"
#include "LinkedList.h"
#include "Date.h"
#

#ifdef __cplusplus
extern "C" {
#endif
    
    
    typedef struct _Inventory{
        List* inventory_items;
        
    }Inventory;
    
    Inventory* inventory_new();
    
    //load from file
    void load_inventory(FILE* fd, Inventory* inventory);
    
    //Will add item and store pointer
    void inventory_add(Inventory* inventory, StockItem* item);
    
    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code);
    
    //helps determine total stock level of NPN transistors
    int count_type_matching_description(char* type, char* description);
    
    //sort by price ascending
    void inventory_sort_by_price_asc(Inventory* inventory);
    
    //helps when determining highest sales volume
    int inventory_sales_volume_for_date(Inventory* inventory, Date* date);
    
    int inventory_count(Inventory* inventory);
    
    
    void inventory_fprint(Inventory* inventory, FILE* fd);
    void inventory_as_string(Inventory* inventory, char* tmp, int tmp_length);
    int inventory_estimate_required_buffer(Inventory* inventory);

#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */

