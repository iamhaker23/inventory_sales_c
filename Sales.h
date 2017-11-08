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

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct Date{
        int dayOfMonth;
        int month;
        int year;
    };
    
    typedef struct _Node{
        StockItem* item;
        Date date;
        int quantity;
        struct _Node* next;
        struct _Node* previous;
    } Node;

    typedef struct _Sales{
        Node* first;
        int length;
        Node* last;
    } Sales;

    Sales* sales_ledger_new();

    //void sales_ledger_fprint(Sales* list, FILE* fd);

    //void sales_ledger_as_string(Sales* list, char *tmp, int tmp_length);

    int sales_ledger_length(Sales* list);

    void sales_ledger_tail_insert(Sales* list, union data_type value);

    //void sales_ledger_head_insert(Sales* list, union data_type value);

    //union data_type sales_ledger_pop_head(Sales* list);

    //union data_type sales_ledger_pop_tail(Sales* list);

    void sales_ledger_empty(Sales* list);

    void sales_ledger_sort(Sales* list, int ascending_flag, int type_sort);

    void sales_ledger_gc(Sales* list);

    //int sales_ledger_memory_size(Sales* list);

    //int sales_ledger_estimate_required_buffer(Sales* list);


#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

