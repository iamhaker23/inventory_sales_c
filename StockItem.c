/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "StockItem.h"

StockItem* item_new(char* line){
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
                
                //omit space, tab and quotes
                if (tmp != ' ' & tmp != '\t' & tmp != '"'){
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
            normalise_resistance(item);
            item->type = type;
            break;
        case(1):
            item = (StockItem*)malloc(sizeof(StockItem));
            item->price_per_unit = atoi(price);
            item->quantity = atoi(quantity);
            item->product_code = code;
            item->description.capacitance.original = desc;
            normalise_capacitance(item);
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
    
    if (item != NULL){
        char* original_line_ptr = (char*)malloc(strlen(line));
        //remove \n char by copying only to length-1
        strncpy(original_line_ptr, line, strlen(line)-1);
        item->original_line_def = original_line_ptr;
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

int stockitem_estimate_required_buffer(StockItem* item){
    //Implementation will simply return the line used to generate the object
    return (strlen(item->original_line_def))+1;
    
}

int stockitem_is_cheaper_than(StockItem* a, StockItem* b){
    int return_value = (a->price_per_unit < b->price_per_unit) ? 1 : 0;
    return_value = (a->price_per_unit > b->price_per_unit) ? -1 : return_value;
    return return_value;
}

void stockitem_as_string(StockItem* item, char* buffer, int buffer_length){
    int est = stockitem_estimate_required_buffer(item);
    if (buffer_length < est ){
        printf("Error: stockitem_as_string() attempted to load %d chars into %d long buffer.\n", est, buffer_length);
    }
    //strncpy(buffer, item->original_line_def, buffer_length);
    snprintf(buffer, buffer_length, item->original_line_def);
}

void normalise_capacitance(StockItem* item){
    int tmp_size = strlen(item->description.capacitance.original);
    char tmp[tmp_size];
    strncpy(tmp, item->description.capacitance.original, tmp_size);
    
    int isAfterRadix = 0;
    double divisor = 1.0f;
    double value = 0.0f;
    if (tmp != NULL){
        for (int i = 0; i < tmp_size; i++){
            char current = tmp[i];
            int charCode = (int)current;
            if (charCode > 47 & charCode < 58){
                //charCode is a digit, add to the next decimal column
                value = (value*10.0f) + (double)((int)charCode%48);
            }else{
                switch(charCode){
                    case(112):
                        //p
                        divisor = pow(10.0f, 12.0f);
                        break;
                    case(110):
                        //n
                        divisor = pow(10.0f, 9.0f);
                        break;
                    case(117):
                        //u
                        divisor = pow(10.0f, 6.0f);
                        break;
                    case(109):
                        //m
                        divisor = pow(10.0f, 3.0f);
                        break;
                    case(70):
                        //F
                        break;
                    case(102):
                        //f
                        break;
                    default:
                        //invalid char
                        printf("Invalid char '%c' encountered when normalising capacitance %s.\n", charCode, tmp);
                        exit(EXIT_FAILURE);
                        break;
                }
                
            }
        }
    }
    item->description.capacitance.normalised_capacitance = value/divisor;
}

void normalise_resistance(StockItem* item){
    int tmp_size = strlen(item->description.resistance.original);
    char tmp[tmp_size];
    strncpy(tmp, item->description.resistance.original, tmp_size);
    
    int isAfterRadix = 0;
    double multiplier = 1.0f;
    double value = 0.0f;
    if (tmp != NULL){
        for (int i = 0; i < tmp_size; i++){
            char current = tmp[i];
            int charCode = (int)current;
            if (charCode > 47 & charCode < 58){
                //charCode is a digit
                if(isAfterRadix == 1){
                    //Add the value, accounting for it's placement after the radix
                    value = value + ((double)((int)charCode%48)/pow(10.0f, (double)isAfterRadix++));
                }else{
                    //Otherwise add next column before radix
                    value = (value*10.0f) + (double)((int)charCode%48);
                }
            }else{
                
                switch(charCode){
                    case(75):
                        //K
                        isAfterRadix = 1;
                        multiplier = 1000.0f;
                        
                        break;
                    case(77):
                        //M
                        isAfterRadix = 1;
                        multiplier = 1000000.0f;
                        break;
                    case(82):
                        //R
                        isAfterRadix = 1;
                        multiplier = 1.0f;
                        break;
                    default:
                        //invalid char
                        printf("Invalid char '%c' encountered when normalising resistance %s.\n", charCode, tmp);
                        exit(EXIT_FAILURE);
                        break;
                }
                
            }
        }
    }
    item->description.resistance.normalised_resistance = value*multiplier;
}