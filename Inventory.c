/*
 * Implementation code of Inventory.h
 * 
 */

    #include "Inventory.h"

    Inventory* inventory_new(){
        
        Inventory* new_inventory = (Inventory*)malloc(sizeof(Inventory));
        if (new_inventory == NULL)
        {
          //Strategy - exit on failure to allocate memory.
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
            //Given a valid input file
            
            //Initialise line buffer
            size_t line_buff_size = 100;
            size_t read = 0;
            char line[line_buff_size];
            char* line_ptr = line;
            
            //load line into line buffer
            while((read = (getline(&line_ptr, &line_buff_size, fd))) && read!=-1 ){
                
                //each line, get StockItem
                StockItem* item = item_new(line);
                
                if (item != NULL){
                    //If correctly created, add to list
                    inventory_add(inventory, item);
                }
            }

        }else{
            //Strategy - exit if invalid file provided.
            printf("Error: NULL file provided.");
            exit(EXIT_FAILURE);
        }
    }

    void inventory_add(Inventory* inventory, StockItem* item){
        
        INode* tmp = (INode*)malloc(sizeof(INode));

        if (tmp == NULL){
            //Strategy - exit on failure to allocate memory.
            fprintf(stderr, "Error: Unable to allocate memory in inventory_add()\n");
            exit(EXIT_FAILURE);
        }
        
        //Assuming product codes must be unique
        //Check if product code is already in inventory
        if (get_item_by_product_code(inventory, item->product_code) != NULL){
            //If attempting to add a duplicate, print error but don't exit
            //Because it doesn't mean entire data is invalid
            fprintf(stderr, "Error: product already exists with code: %s.\n", item->product_code);
            return;
        }

        tmp->item = item;
        tmp->next = NULL;
        tmp->previous = inventory->last;

        if(inventory->last == NULL){
            //Empty list, so new element is both first and last
            inventory->last = inventory->first = tmp;
        }else{
            //The last element of the list is now tmp, and whatever WAS the last element now points to tmp
            inventory->last = inventory->last->next = tmp;
        }
        //maintain length
        inventory->length=inventory->length+1;

    }

    //helps when modifying stock levels per sale
    StockItem* get_item_by_product_code(Inventory* inventory, char* code){

        //traverse list (forward)
        INode* current = inventory->first;
        
        while(current!=NULL){
            StockItem* tmp = current->item;
            if (strcmp(tmp->product_code, code)==0){
                //if this product has the product code, return it immediately.
                return tmp;
            }
            current = current->next;
        }
        //Did not find a match, so return NULL
        return NULL;
    }

    //Q3, determine total stock level of NPN transistors
    int count_type_matching_description_in_stock(Inventory* inventory, char* type, char* description){
        
        //get a subset of stock matching the item search, and return the length
        int output = get_subset_of_in_stock(inventory, type, description)->length;
        return output;
    }
    
    float total_resistance_of_in_stock_resistors(Inventory* inventory){
        
        //initialise total
        float total_resistance = 0.0f;
        
        //get subset of stock that is just "resistors"
        Inventory* subset = get_subset_of_in_stock(inventory, "resistor", NULL);
        
        //traverse list (forward)
        INode* current = subset->first;
        
        while(current != NULL){
            //add each resistance to total
            total_resistance = total_resistance + current->item->description.resistance.normalised_resistance;
            
            current = current->next;
        }
        //return total
        return total_resistance;
        
    }
    
    Inventory* get_subset_of_in_stock(Inventory* inventory, char* type, char* description){
        
        Inventory* subset = inventory_new();
        
        //traverse given list (forward)
        INode* current = inventory->first;
        while(current != NULL){
            
            //switch search algorithm depending on StockItem type being searched for
            //Note: this search is only implemented for resistors(0) and transistors(3)
            int type_switch = get_switch(type);
            switch(type_switch){
                
                case(0):
                    //Searching for resistor
                    //if in stock
                    if (current->item->quantity > 0){
                        if(strncmp(current->item->type, "resistor", 8) == 0){  
                            if (description != NULL){
                                //If search requires a match on description, check for a match (i.e BS1852 encoded resistance with resistance.original)
                                if(strncmp(current->item->description.resistance.original, description, strlen(description)) == 0){
                                    //If matching, add it to the resultset
                                   inventory_add(subset, current->item);
                                }   
                            }else{
                                //if no description match is required
                                //then the current item is already a match for this search
                                inventory_add(subset, current->item);
                            }
                        }
                    }
                    break;
                case(3):
                    //Searching for transistor
                    //if in stock
                    if (current->item->quantity > 0){
                        //if current item matches type
                        if(strncmp(current->item->type, "transistor", 10) == 0){
                            if (description != NULL){
                                //If search requires a match on description, check for a match (i.e. transistor_config)
                                if(strncmp(current->item->description.transistor_config, description, strlen(description)) == 0){
                                    //If matching, add it the resultset
                                    inventory_add(subset, current->item);
                                }
                            }else{
                                //if no description match is required
                                //then the current item is already a match for this search
                                inventory_add(subset, current->item);
                            }
                        }
                    }
                    break;
                default:
                    //No search algorithm implemented for given StockItem type, so exit immediately.
                    printf("Error: count type matching description is not implemented for %s (type_switch:%d).\n", type, type_switch);
                    exit(EXIT_FAILURE);
                    break;
            }
            current = current->next;
        }
        //return subset of all matches
        return subset;
    }

    void inventory_as_string(Inventory* inventory, char* tmp, int tmp_length){
        //stop immediately if the buffer is not large enough
        int est = inventory_estimate_required_buffer(inventory);
        if (tmp_length < est ){
            printf("Error: inventory_as_string() attempted to load %d bytes into %d buffer.\n", est, tmp_length);
            exit(EXIT_FAILURE);
        }

        //Quickly detect empty inventory
        if (inventory_length(inventory) == 0){
            snprintf(tmp, tmp_length, "List is empty.");

        }else{
            //initialise output buffer with an opening bracket
            snprintf(tmp, tmp_length, "( ");
            
            //traverse inventory list (forward)
            INode* current = inventory->first;
            while(current != NULL){
                StockItem* item = current->item;
                
                //get item_as_string
                int buffer_length = stockitem_estimate_required_buffer(item);
                char item_as_string[buffer_length+1];
                stockitem_as_string(item, item_as_string, buffer_length+1);
                
                //add item_as_string to inventory string
                snprintf(tmp + strlen(tmp), tmp_length, (current->next==NULL) ?"[%s]" : "[%s], ", item_as_string);
                current = current->next;
            }
            //Add closing bracket
            snprintf(tmp + strlen(tmp),tmp_length, " )");
        }
    }
    
    void inventory_as_csv(Inventory* inventory, char* tmp, int tmp_length){
        //stop immediately if the buffer is not large enough
        int est = inventory_estimate_required_buffer(inventory);
        if (tmp_length < est ){
            printf("Error: inventory_as_string() attempted to load %d bytes into %d buffer.\n", est, tmp_length);
            exit(EXIT_FAILURE);
        }

        //Quickly detect empty list
        if (inventory_length(inventory) == 0){
            snprintf(tmp, tmp_length, "List is empty.");

        }else{
            //initialise buffer with a newline
            snprintf(tmp, tmp_length, "\r\n");
            //Traverse inventory list (forward)
            INode* current = inventory->first;
            while(current != NULL){
                StockItem* item = current->item;
                
                //get item_as_string
                int buffer_length = stockitem_estimate_required_buffer(item);
                char item_as_string[buffer_length+1];
                stockitem_as_string(item, item_as_string, buffer_length+1);
                
                //Add item_as_string to inventory string
                snprintf(tmp + strlen(tmp), tmp_length, "%s\r\n", item_as_string);
                current = current->next;
            }
            //Buffer now contains items as lines, based on stockitem_as_string formatting
        }
    }

    int inventory_estimate_required_buffer(Inventory* inventory){
        //return Length of buffer x Sensible maximum width
        int estimated_length = inventory_length(inventory)*50;
        return estimated_length;
    }

    void inventory_sort(Inventory* list, int ascending_flag){
    //list contains more than one item
    if(list->first != list->last){
        
        int swapTakenPlace;
        
        //loop until no sorting is required on list
        do{
            //initialise sorted flag - "sorting did not take place this iteration"
            swapTakenPlace = 0;
            //traverse list (forward)
            for(INode* node = list->first; node->next != NULL; node=node->next){
                //if swapping 
                if (((ascending_flag == 1) && (node->item->price_per_unit > node->next->item->price_per_unit )) || ((ascending_flag == 0) && (node->item->price_per_unit < node->next->item->price_per_unit ))){
                   
                   //swap
                   StockItem* tmp = node->item ;
                   node->item = node->next->item;
                   node->next->item  = tmp;
                   
                   //flag - "sorting did take place on this iteration"
                   swapTakenPlace = 1;
                }
            }
        //loop if sorting took place (because further sorting may be required)
        }while(swapTakenPlace);
    }
}
    
    void inventory_empty(Inventory* inventory){
        //Traverse inventory (forward)
        INode* node;
    
        while(inventory->first != NULL){
            node = inventory->first;
            
            //unlink current head (point head at next element)
            inventory->first = node->next;
            
            //remove unlinked head
            free(node);
        }
        
        //update last pointer to indicate list is empty
        inventory->last = NULL;
    }
    
    void inventory_gc(Inventory* inventory){
        //clear list elements
        inventory_empty(inventory);
        //free pointer to inventory
        free(inventory);
    }
    