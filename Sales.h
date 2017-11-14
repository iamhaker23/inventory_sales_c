/* 
 * File:   Sales.h
 * Author: Hakeem
 *
 * 
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
    
    //defines a simple date as its component parts
    typedef struct _Date{
        int dayOfMonth;
        int month;
        int year;
    }Date;
    
    //defines a wrapper for metrics relating to a specific date of sales transactions
    typedef struct _Sales_Volume{
        Date* date;
        int volume;
        int pence_spent;
        int failed_transactions;
    }Sales_Volume;
    
    //defines a node linked in a Sales Ledger list
    typedef struct _SNode{
        StockItem* item;
        Date date;
        int quantity;
        struct _SNode* next;
        struct _SNode* previous;
    } SNode;

    //defines the pointers and length of a Sales Ledger list (doubly linked list)
    typedef struct _Sales{
        SNode* first;
        int length;
        SNode* last;
    } Sales;

    //allocate memory for a new sales ledger
    Sales* sales_ledger_new();

    //count number of items in list
    int sales_ledger_length(Sales* list);

    //add a new transaction to the Sales Ledger list 
    void sales_ledger_add(Sales* list, StockItem* item, Date date, int quantity);

    //free all elements of the list
    void sales_ledger_empty(Sales* list);

    //sort transactions by date assc/desc (based on ascending flag)
    void sales_ledger_sort(Sales* list, int ascending_flag);

    //remove list and elements from memory
    void sales_ledger_gc(Sales* list);
    
    //Indicate whether a is earlier(-1) equal(0) or later(1) than  b
    int datecmp(Date* a, Date* b);
    
    //load from file
    void load_sales_ledger(FILE* fd, Sales* list, Inventory* inventory);
    
    //Store a date in memory (so it can be referenced outside the scope of initialising code)
    Date date_malloc(char* date);
    
    //Convert a date to a human-readable string
    void date_as_string(Date date, char* date_str, int buff_size);
    
    //Estimate buffer size required to print Sales Ledger as a human readable string
    int sales_ledger_estimate_required_buffer(Sales* sales);
    
    //Load Sales Ledger as a human-readable string into sales_string
    void sales_ledger_as_string(Sales* sales, char* sales_string, int estimated_length);

    //apply all transactions to given inventory (i.e. update quantities or report failed transactions)
    Sales_Volume* apply_sales_to_inventory(Sales* sales, Inventory* inventory, FILE* log);

    //Store a Sales Volume in memory (so it can be referenced outside the scope of initialising code)
    Sales_Volume* sales_volume_new();
    
#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

