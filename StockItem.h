/* 
 * File:   StockItem.h
 * Author: Hakeem
 *
 * 
 */

#ifndef STOCKITEM_H
#define STOCKITEM_H

#ifdef __cplusplus
extern "C" {
#endif
    
    //metadata for a resistance rating
    typedef struct _Resistance{
        float normalised_resistance;
        char* original;
    } Resistance;
    
    //metadata for capacitance rating
    typedef struct _Capacitance{
        float normalised_capacitance;
        char* original;
    } Capacitance;
    
    //union interpretations of "description"
    union description{
        //It could be an IC description
        char* ic_desc;
        //It could be a transistor configuration
        char* transistor_config;
        //It could be a resistance rating
        Resistance resistance;
        //Or it could be a capacitance rating
        Capacitance capacitance;
    };

    //Stock item fields, including a union "description" field
    typedef struct _StockItem{
        char* type;
        char* product_code;
        int price_per_unit;
        int quantity;
        union description description;
        char* original_line_def;
    } StockItem;

    //Parse line into a newly created StockItem
    //returns a reference to newly created StockItem
    StockItem* item_new(char* line);
    
    //Returns an integer representing the difference b-a
    int stockitem_is_cheaper_than(StockItem* a, StockItem* b);
    
    //Populates buffer with the a human-readable string representing StockItem
    void stockitem_as_string(StockItem* item, char* buffer, int buffer_length);
    
    //convert item's string capacitance rating into a floating point value, stores both in StockItem
    void normalise_capacitance(StockItem* item);
    
    //convert item's string resistance rating into a floating point value, stores both in StockItem
    void normalise_resistance(StockItem* item);
    
    //Get the universal flag representing given type (used for switch-cases)
    int get_switch(char* type);
    
    //Estimate required size in bytes to store human-readable string representation of given StockItem
    int stockitem_estimate_required_buffer(StockItem* item);
    
    //Allocate memory and initialise with a copy of given string, returns a pointer to new copy
    char* str_malloc(char* value);
    
    //Allocate memory and initialise with int parsed from given string, returns a new copy
    int int_malloc(char* value);
    
#ifdef __cplusplus
}
#endif

#endif /* STOCKITEM_H */

