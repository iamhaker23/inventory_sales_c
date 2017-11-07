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

    }

    //Will add item and store pointer
    void inventory_add(Inventory* inventory, StockItem* item){
        
        if (get_item_by_product_code(inventory, item->product_code) != NULL){
            printf("Error: product already exists with code: %s.\n", item->product_code);
        }else{
            list_tail_insert(inventory->inventory_items, get_data_type_stockitem(item));
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
    int count_type_matching_description(char* type, char* description){

    }

    //sort by price ascending
    void inventory_sort_by_price_asc(Inventory* inventory){

    }

    //helps when determining highest sales volume
    int inventory_sales_volume_for_date(Inventory* inventory, Date* date){

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
            snprintf(tmp, sizeof(tmp), "List is empty.");
        }else{
            snprintf(tmp, sizeof(tmp), "( ");
            Node* current = inventory->inventory_items->first;
            while(current != NULL){
                StockItem* item = current->value.item;
                int buffer_length = stockitem_estimate_required_buffer(item);
                char* item_as_string[buffer_length];
                stockitem_as_string(item, item_as_string, buffer_length);
                snprintf(tmp + strlen(tmp), sizeof(tmp), (current->next==NULL) ?"[%s]" : "[%s], ", item_as_string);
                current = current->next;
            }
            snprintf(tmp + strlen(tmp), sizeof(tmp), " )", inventory->inventory_items);
        }
    }
    
    int inventory_estimate_required_buffer(Inventory* inventory){
        int estimated_length = inventory_count(inventory)*50;
        return estimated_length;
    }