/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "StockItem.h"

StockItem* new_item(char* line){
    const int MAX_FIELD_LENGTH = 20;
    
    //ONE MUST INITIALISE THE CHARACTER ARRAY BUFFERS OR THEY WILL REFERENCE ARBITRARY MEMORY!
    char type[20] = "\0";
    char code[20] = "\0";
    char quantity[20] = "\0";
    char price[20] = "\0";
    char desc[20] = "\0";
    
    //sscanf(line, "%c,\t%c,\t%c,\t%c,\t%c\n", type, code, quantity, price, desc);
    
    
    //useless --- reads memory not the string object... gibberish output :'(
    int index = 0;
    const int NUM_FIELDS = 5;
    
    for (int i = 1; i <= NUM_FIELDS; i++){
        char tmp = line[index++];
        if (tmp != '\n'){
            while (tmp != ',' & tmp != '\n'){
                if (tmp != ' '){
                    switch(i){
                       case(1):
                           snprintf(type, MAX_FIELD_LENGTH, "%s%c", type, tmp);
                           break;
                       case(2):
                           snprintf(code, MAX_FIELD_LENGTH, "%s%c", code, tmp);
                           break;
                       case(3):
                           snprintf(quantity, MAX_FIELD_LENGTH, "%s%c", quantity, tmp);
                           break;
                       case(4):
                           snprintf(price, MAX_FIELD_LENGTH, "%s%c", price, tmp);
                           break;
                       case(5):
                           snprintf(desc, MAX_FIELD_LENGTH, "%s%c", desc, tmp);
                           break;
                       default:
                           break;
                    }
                }
                tmp = line[index++];
            }
        }
    }
    
    StockItem* item = NULL;
    
    int type_switch = get_switch(type);
    
    switch(type_switch){
        case(0):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            item->description.resistance.original = desc;
            item->type = type;
            break;
        case(1):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            item->description.capacitance.original = desc;
            item->type = type;
            break;
        case(2):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            
            //One NULL to rule them all, one NULL to find them, One NULL to bring them all and in the darkness bind them.
            item->description.transistor_config = NULL;
            
            item->type = type;
            break;
        case(3):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            item->description.transistor_config = desc;
            item->type = type;
            break;
        case(4):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            item->description.ic_desc = desc;
            item->type = type;
            break;
        default:
            printf("Unknown type: %s\n", type);
            exit(EXIT_FAILURE);
            break;
    }
    return item;
}

int get_switch(char* type){
    
    int output = -1;
    
    //Should do this with an array and use index to represent "switch" value
    if (strcmp(type, "resistor") == 0){output = 0;}
    else if (strcmp(type, "capacitor") == 0){output = 1;}
    else if (strcmp(type, "diode") == 0){output = 2;}
    else if (strcmp(type, "transistor") == 0){output = 3;}
    else if (strcmp(type, "IC") == 0){output = 4;}
    
    return output;
}

int stockitem_is_cheaper_than(StockItem* a, StockItem* b){
    
}

void stockitem_as_string(StockItem* item, char* buffer){
    
}

int is_valid(char* type){
    
}

void normalise_capacitance(StockItem* item){
    
}

void normalise_resistance(StockItem* item){
    
}