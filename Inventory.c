/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

    #include "Inventory.h"

    Inventory* inventory_new(){
        Inventory* new_inventory = (Inventory*)malloc(sizeof(Inventory));
        if (new_inventory == NULL)
        {
          fprintf(stderr, "Error: Unable to allocate memory in list_new()\n");

          exit(EXIT_FAILURE);
        }

        new_inventory->first = NULL;
        new_inventory->last  = NULL;
        new_inventory->length = 0;

        return new_inventory; 
    }

    
    int inventory_length(Inventory* inventory){
        return inventory->length;
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
    void inventory_add(Inventory* inventory, StockItem* item){

        INode* tmp = (INode*)malloc(sizeof(INode));

        if (tmp == NULL){
            fprintf(stderr, "Error: Unable to allocate memory in list_tail_insert()\n");
            exit(EXIT_FAILURE);
        }

        tmp->item = item;
        tmp->next = NULL;
        tmp->previous = inventory->last;

        if(inventory->last == NULL){
            inventory->last = inventory->first = tmp;
        }else{
            //The last element of the list is now tmp, and whatever WAS the last element now points to tmp
            inventory->last = inventory->last->next = tmp;
        }

        inventory->length=inventory->length+1;

    }

    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code){
        StockItem* item = NULL;

        INode* current = inventory->first;
        while(current!=NULL){
            StockItem* tmp = current->item;
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

        INode* current = inventory->first;
        while(current != NULL){
            int type_switch = get_switch(type);
            switch(type_switch){
                //only implemented for transistors
                case(3):
                    if(strncmp(current->item->type, type, strlen(type)) == 0){
                        if(strncmp(current->item->description.transistor_config, description, strlen(description)) == 0){
                            output++;
                        }
                    }
                    break;
                default:
                    printf("Error: count type matching description is not implemented for %s (type_switch:%d).\n", type, type_switch);
                    return -1;
                    break;
            }
            current = current->next;
        }

        return output;
    }

    void inventory_as_string(Inventory* inventory, char* tmp, int tmp_length){
        //stop if the buffer is not large enough
        int est = inventory_estimate_required_buffer(inventory);
        if (tmp_length < est ){
            printf("Error: inventory_as_string() attempted to load %d bytes into %d buffer.\n", est, tmp_length);
            exit(EXIT_FAILURE);
        }

        if (inventory_length(inventory) == 0){
            snprintf(tmp, tmp_length, "List is empty.");

        }else{
            snprintf(tmp, tmp_length, "( ");
            INode* current = inventory->first;
            while(current != NULL){
                StockItem* item = current->item;
                int buffer_length = stockitem_estimate_required_buffer(item);
                char item_as_string[buffer_length];
                stockitem_as_string(item, item_as_string, buffer_length);
                snprintf(tmp + strlen(tmp), tmp_length, (current->next==NULL) ?"[%s]" : "[%s], ", item_as_string);
                current = current->next;
            }
            snprintf(tmp + strlen(tmp),tmp_length, " )", inventory);
        }
    }

    int inventory_estimate_required_buffer(Inventory* inventory){
        int estimated_length = inventory_length(inventory)*50;
        return estimated_length;
    }

    void inventory_sort(Inventory* list, int ascending_flag){
    if(list->first != list->last){
        //list contains more than one item
        int sorted;
        if (ascending_flag == 1){
            do{
                sorted = 1;
                for(INode* node = list->first; node->next != NULL; node=node->next){
                    if (node->item->price_per_unit > node->next->item->price_per_unit ){
                       //swap

                       StockItem* tmp = node->item ;
                       node->item = node->next->item;
                       node->next->item  = tmp;

                       sorted = 0;
                    }
                }
            }while(!sorted);
        }else{
            do{
                sorted = 1;
                for(INode* node = list->first; node->next != NULL; node=node->next){
                    if (node->item->price_per_unit < node->next->item->price_per_unit ){
                       //swap

                       StockItem* tmp = node->item ;
                       node->item = node->next->item;
                       node->next->item  = tmp;

                       sorted = 0;
                    }
                }
            }while(!sorted);
        }
    }
}
    
    void inventory_empty(Inventory* inventory){
        INode* node;
    
        while(inventory->first != NULL){
            INode* node = inventory->first;
            inventory->first = node->next;
            free(node);
        }

        inventory->last = NULL;
    }
    
    void inventory_gc(Inventory* inventory){
        inventory_empty(inventory);
        free(inventory);
    }
    