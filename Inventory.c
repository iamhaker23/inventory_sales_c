/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Inventory.h"

    Inventory* inventory_new(){
        Inventory* new_inventory = (Inventory*)malloc(sizeof(Inventory));
        if (new_inventory == NULL){
            printf("Unable to allocate memory in inventory_new();");
            exit(EXIT_FAILURE);
        }

        new_inventory->inventory_items = list_new();

        return new_inventory;
    }


    //load from file
    void load_inventory(FILE* fd, Inventory* inventory){
        if (fd != NULL){
            size_t line_buff_size = 100;
            size_t read = 0;
            char line[line_buff_size];
            char* line_ptr = line;
            
            while((read = (getline(&line_ptr, &line_buff_size, fd))) && read!=-1 ){
                StockItem* item = item_new(line);
                inventory_add(inventory, item);
            }
            
        }else{
            printf("Error: NULL file provided.");
            exit(EXIT_FAILURE);
        }
    }

    //Will add item and store pointer
    int inventory_add(Inventory* inventory, StockItem* item){
        
        if (item == NULL){
            printf("Cannot add NULL to inventory.\n");
            return -1;
        }
        
        if (get_item_by_product_code(inventory, item->product_code) != NULL){
            printf("Error: product already exists with code: %s.\n", item->product_code);
            return -1;
        }else{
            list_tail_insert(inventory->inventory_items, get_data_type_stockitem(item));
            return 1;
        }
    }

    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code){
        StockItem* item = NULL;
        
        Node* current = inventory->inventory_items->first;
        while(current!=NULL){
            StockItem* tmp = current->value.item;
            if (strcmp(tmp->product_code, code)==0){
                item = tmp;
            }
            current = current->next;
        }
        
        return item;
    }

    //helps determine total stock level of NPN transistors
    int count_type_matching_description(Inventory* inventory, char* type, char* description){
        int output = 0;
        
        Node* current = inventory->inventory_items->first;
        while(current != NULL){
            int type_switch = get_switch(type);
            switch(type_switch){
                //only implemented for transistors
                case(3):
                    if(strncmp(current->value.item->type, type, strlen(type)) == 0){
                        if(strncmp(current->value.item->description.transistor_config, description, strlen(description)) == 0){
                            output++;
                        }
                    }
                    break;
                default:
                    printf("Error: count type matching description is not implemented for %s (typeswitch:%d).\n", type, type_switch);
                    return -1;
                    break;
            }
            current = current->next;
        }
        
        return output;
    }

    //sort by price ascending
    void inventory_sort_by_price(Inventory* inventory, int ascending_flag){
        list_sort(inventory->inventory_items, ascending_flag, 2);
    }
    
    int inventory_count(Inventory* inventory){
        return list_length(inventory->inventory_items);
    }
    
    void inventory_fprint(Inventory* inventory, FILE* fd){
        int estimated_length = inventory_estimate_required_buffer(inventory);
        char output[estimated_length];
        inventory_as_string(inventory, output, estimated_length);
        fprintf(fd, output);
    }
    
    void inventory_as_string(Inventory* inventory, char* tmp, int tmp_length){
        //stop if the buffer is not large enough
        int est = inventory_estimate_required_buffer(inventory);
        if (tmp_length < est ){
            printf("Error: inventory_as_string() attempted to load %d bytes into %d buffer.\n", est, tmp_length);
            exit(EXIT_FAILURE);
        }

        if (inventory_count(inventory) == 0){
            snprintf(tmp, tmp_length, "List is empty.");
            
        }else{
            snprintf(tmp, tmp_length, "( ");
            Node* current = inventory->inventory_items->first;
            while(current != NULL){
                StockItem* item = current->value.item;
                int buffer_length = stockitem_estimate_required_buffer(item);
                char item_as_string[buffer_length];
                stockitem_as_string(item, item_as_string, buffer_length);
                snprintf(tmp + strlen(tmp), tmp_length, (current->next==NULL) ?"[%s]" : "[%s], ", item_as_string);
                current = current->next;
            }
            snprintf(tmp + strlen(tmp),tmp_length, " )", inventory->inventory_items);
        }
    }
    
    int inventory_estimate_required_buffer(Inventory* inventory){
        int estimated_length = inventory_count(inventory)*50;
        return estimated_length;
    }