/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sales.h
 * Author: Hakeem
 *
 * Created on 03 November 2017, 12:07
 */

#ifndef SALES_H
#define SALES_H

#include "StockItem.h"
#include "Inventory.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct _Date{
        int dayOfMonth;
        int month;
        int year;
    }Date;
    
    typedef struct _Sales_Volume{
        Date date;
        int volume;
        int pence_spent;
    }Sales_Volume;
    
    typedef struct _SNode{
        StockItem* item;
        Date date;
        int quantity;
        struct _SNode* next;
        struct _SNode* previous;
    } SNode;

    typedef struct _Sales{
        SNode* first;
        int length;
        SNode* last;
    } Sales;

    int datecmp(Date* a, Date* b);
    
    //load from file
    void load_sales_ledger(FILE* fd, Sales* list, Inventory* inventory);
    
    Sales* sales_ledger_new();

    int sales_ledger_length(Sales* list);

    void sales_ledger_add(Sales* list, StockItem* item, Date date, int quantity);

    void sales_ledger_empty(Sales* list);

    void sales_ledger_sort(Sales* list, int ascending_flag);

    void sales_ledger_gc(Sales* list);

    Date sales_ledger_highest_volume_day(Sales* list);
    
    Date date_malloc(char* date);
    
    void date_as_string(Date date, char* date_str, int buff_size);
    
    int sales_ledger_estimate_required_buffer(Sales* sales);
    
    void sales_ledger_as_string(Sales* sales, char* sales_string, int estimated_length);

    Sales_Volume* apply_sales_to_inventory(Sales* sales, Inventory* inventory);

    Sales_Volume* sales_volume_new();
    
#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

