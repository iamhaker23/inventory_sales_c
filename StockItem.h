/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StockItem.h
 * Author: Hakeem
 *
 * Created on 03 November 2017, 12:08
 */

#ifndef STOCKITEM_H
#define STOCKITEM_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct _Resistance{
        float normalised_resistance;
        char* original;
    } Resistance;
    
    typedef struct _Capacitance{
        float normalised_capacitance;
        char* original;
    } Capacitance;
    
    union description{
        char* ic_desc;
        char* transistor_config;
        Resistance resistance;
        Capacitance capacitance;
    };

    typedef struct _StockItem{
        char* type;
        char* product_code;
        int price_per_unit;
        int quantity;
        union description description;
    } StockItem;

    
    StockItem* new_item(char* line);
    int stockitem_is_cheaper_than(StockItem* a, StockItem* b);
    void stockitem_as_string(StockItem* item, char* buffer);
    int is_valid(char* type);
    void normalise_capacitance(StockItem* item);
    void normalise_resistance(StockItem* item);
    int get_switch(char* type);
#ifdef __cplusplus
}
#endif

#endif /* STOCKITEM_H */

