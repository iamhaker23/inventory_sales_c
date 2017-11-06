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
#include "StockItem.h"
#include "LinkedList.h"
#include "Date.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    typedef struct _Inventory{
        List* inventory_items;
        
    }Inventory;
    
    //load from file
    void load_inventory(FILE* fd, Inventory* inventory);
    
    //Will add item and store pointer
    void add_item(Inventory* inventory, StockItem* item);
    
    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code);
    
    //sort by price ascending
    void sort_by_price_asc(Inventory* inventory);
    
    //helps when determining highest sales volume
    int get_sales_volume_for_date(Inventory* inventory, Date* date);
    
    

#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */

