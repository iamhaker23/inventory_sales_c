/*
 * Implementation code of Sales.h
 */

#include <stdint.h>

#include "Sales.h"
#include "Inventory.h"

    Sales* sales_ledger_new(){
        Sales* new_list = (Sales*)malloc(sizeof(Sales));
        if (new_list == NULL)
            
        {
            //Strategy - exit immediately if memory cannot be allocated
          fprintf(stderr, "Error: Unable to allocate memory in list_new()\n");
          exit(EXIT_FAILURE);
        }

        new_list->first = NULL;
        new_list->last  = NULL;
        new_list->length = 0;

        return new_list; 
    }

    int sales_ledger_length(Sales* list){
        //length is maintained in "add", no need to calculate
        return list->length;
    }

    void sales_ledger_add(Sales* list, StockItem* item, Date date, int quantity){
        //Allocate memory for a new SNode
        SNode* tmp = (SNode*)malloc(sizeof(SNode));

        if (tmp == NULL){
            //Strategy - exit immediately if cannot allocate memory.
            fprintf(stderr, "Error: Unable to allocate memory in list_tail_insert()\n");
            exit(EXIT_FAILURE);
        }

        //initialise new SNode with given values
        tmp->item = item;
        tmp->date = date;
        tmp->quantity = quantity;
        tmp->next = NULL;
        tmp->previous = list->last;

        if(list->last == NULL){
            //if list is empty, this is the first and last element
            list->last = list->first = tmp;
        }else{
            //otherwise, link to list tail
            //The last element of the list is now tmp, and whatever WAS the last element now points to tmp
            list->last = list->last->next = tmp;
        }
        
        //maintain length counter
        list->length=list->length+1;
    }

    void sales_ledger_empty(Sales* list){
        //Traverse sales (forward)
        SNode* node;
    
        while(list->first != NULL){
            //get current head
            node = list->first;
            //unlink current head, point head to next element
            list->first = node->next;
            //free unlinked head
            free(node);
        }
        //update pointer to indicate empty list
        list->last = NULL;
    }

    
    void sales_ledger_sort(Sales* list, int ascending_flag){
        if(list->first != list->last){
            //list contains more than one item
            int swapTakenPlace;
            //loop until no sorting is required on list
            do{
                //initialise sorted flag - "sorting did not take place this iteration"
                swapTakenPlace = 0;
                //Traverse list (forward)
                for(SNode* node = list->first; node->next != NULL; node=node->next){
                    //if swapping
                    if (((ascending_flag == 1) && (datecmp(&(node->date), &(node->next->date)) > 0 )) || ((ascending_flag == 0) && (datecmp(&(node->date), &(node->next->date)) < 0 ))){
                       
                        //swap
                       StockItem* tmp_item = node->item ;
                       int tmp_quantity = node->quantity;
                       Date tmp_date = node->date;

                       node->item = node->next->item ;
                       node->date = node->next->date ;
                       node->quantity = node->next->quantity ;

                       node->next->item  = tmp_item;
                       node->next->date  = tmp_date;
                       node->next->quantity  = tmp_quantity;
                       
                       //flag - "sorting did take place on this iteration"
                       swapTakenPlace = 1;
                       
                    }
                }
            }while(swapTakenPlace);
        }
    }

    
    void sales_ledger_gc(Sales* list){
        //Remove all elements
        sales_ledger_empty(list);
        //Free pointer to list
        free(list);
    }
    
    int datecmp(Date* a, Date* b){
        //initialise output for the case "a == b"
        int output = 0;
        
        //bias NULL to represent "earliest possible date"
        if (a == NULL){
            return -1;
        }
        if (b == NULL){
            return 1;
        }
        
        //detect whether a is later or earlier
        if ((a->year > b->year) || (a->year == b->year && a->month > b-> month) || (a->year == b->year && a->month == b->month && a->dayOfMonth > b->dayOfMonth)){
            //a is later
            output = 1;
        }else if ((a->year < b->year) || (a->year == b->year && a->month < b-> month) || (a->year == b->year && a->month == b->month && a->dayOfMonth < b->dayOfMonth)){
            //a is earlier
            output = -1;
        }
        
        return output;
        
    }
    
    //load from file
    void load_sales_ledger(FILE* fd, Sales* list, Inventory* inventory){
        if (fd != NULL){
            //File is valid
            
            //Initialise line buffer
            size_t line_buff_size = 100;
            char line[line_buff_size];

            //Loop while we can get a line from the file
            while(fgets(line, line_buff_size, fd)!=NULL ){
                //Note: following parsing code based on StockItem.c implementation
                
                if (line[0] == '\n' || line[0] == '\r'){
                    //nothing to do for an empty line, continue reading rest of file
                    continue;
                }
                
                //initialise fields to be read from line
                char quantity[20] = "\0";
                char date[20] = "\0";
                char code[20] = "\0";
                
                int index = 0;
                const int NUM_FIELDS = 3;
                const int MAX_FIELD_LENGTH = 20;

                for (int i = 1; i <= NUM_FIELDS; i++){
                    //Get the first character of the field
                    char tmp = line[index++];
                    
                    //If field begins newline, assume empty field and do not parse
                    if (tmp != '\n' && tmp != '\r'){
                       
                        //while end of field is not reached
                        while (tmp != ',' && tmp != '\n' && tmp != '\r'){
                            
                            //omit space, tab and quotes
                            //Note: check else branch
                            if (tmp != ' ' && tmp != '\t' && tmp != '"'){
                                
                                //switch parsing behaviour according to field
                                switch(i){
                                   case(1):
                                       //append character to field value
                                       snprintf(date, MAX_FIELD_LENGTH, "%s%c", date, tmp);
                                       //peek ahead
                                       tmp = line[index++];
                                       //if end of field detected, append a string terminator to field '\0'
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(date, MAX_FIELD_LENGTH, "%s%c", date, '\0');
                                       }
                                       break;
                                   case(2):
                                       //append character to field value
                                       snprintf(code, MAX_FIELD_LENGTH, "%s%c", code, tmp);
                                       //peek ahead
                                       tmp = line[index++];
                                       //if end of field detected, append a string terminator to field '\0'
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(code, MAX_FIELD_LENGTH, "%s%c", code, '\0');
                                       }
                                       break;
                                   case(3):
                                       //append character to field value
                                       snprintf(quantity, MAX_FIELD_LENGTH, "%s%c", quantity, tmp);
                                       //peek ahead
                                       tmp = line[index++];
                                       //if end of field detected, append a string terminator to field '\0'
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(quantity, MAX_FIELD_LENGTH, "%s%c", quantity, '\0');
                                       }
                                       break;
                                   default:
                                       //field counter incorrectly initialised, just skip character
                                       fprintf(stderr, "NUM_FIELDS incorrectly assigned: load_sales_ledger()\n");
                                       tmp = line[index++];
                                       break;
                                }
                            }else{
                                //Move to next character
                                tmp = line[index++];
                            }

                        }
                    }
                }
                
                
                StockItem* item = get_item_by_product_code(inventory, code);
                if (item != NULL){
                    //If item exists, add sale to Sales Ledger list
                    Date date_obj = date_malloc(date);
                    int quantity_obj = int_malloc(quantity);
                    sales_ledger_add(list, item, date_obj, quantity_obj);
                }else{
                    //Item is not in inventory, but continue as rest of data may be valid.
                    fprintf(stderr, "Could not load transaction for %s: Item doesn't exist.\n", code);
                }
            }

        }else{
            //Stop immediately if the sales file is invalid
            printf("Error: NULL file provided.");
            exit(EXIT_FAILURE);
        }
    }
    
    Date date_malloc(char* date){
        //strictly converts a 10 character DD/MM/YYYY string
        
        if (strlen(date) != 10 || date[2] != '/' || date[5] != '/'){
            //String is incorrect format
            //Stop immediately otherwise undefined behaviour would occur
            fprintf(stderr, "Could not convert date: %s.\n", date);
            exit(EXIT_FAILURE);
        }
        
        //Allocate memory for date (so it can be referenced outside initialising code scope)
        Date* output = (Date*)malloc(sizeof(Date));
       
        //convert string into integer parts
        char part[4] ="0000";
        snprintf(part, 5, "00%c%c", date[0], date[1]);
        int dayOfMonth = atoi(part);
        
        snprintf(part, 5, "00%c%c", date[3], date[4]);
        int month = atoi(part);
        
        snprintf(part, 5, "%c%c%c%c", date[6], date[7], date[8], date[9]);
        int year = atoi(part);
        
        //load values into newly created Date
        output->dayOfMonth = dayOfMonth;
        output->month = month;
        output->year = year;
        
        return *output;
    }
    
    void date_as_string(Date date, char* date_str, int buff_size){
        if (buff_size < 10){
            //Exit immediately as buffer cannot contain date string
            fprintf(stderr, "Could not load datestring into %d buffer.\n", buff_size);
            exit(EXIT_FAILURE);
        }
        //load buffer with date string
        snprintf(date_str, 11, "%.2d/%.2d/%.4d", date.dayOfMonth, date.month, date.year);
    }
    
    int sales_ledger_estimate_required_buffer(Sales* sales){
        return sales->length*50;
    }
    
    void sales_ledger_as_string(Sales* sales, char* sales_string, int estimated_length){
        
        //Note: undefined behaviuour if sales_string is not empty.

        //stop if the buffer is not large enough
        int est = sales_ledger_estimate_required_buffer(sales);
        if (estimated_length < est ){
            printf("Error: inventory_as_string() attempted to load %d bytes into %d buffer.\n", est, estimated_length);
            exit(EXIT_FAILURE);
        }

        if (sales_ledger_length(sales) == 0){
            snprintf(sales_string, estimated_length, "List is empty.");
        }else{
            snprintf(sales_string, estimated_length, "( ");
            SNode* current = sales->first;
            while(current != NULL){
                char date_str[10] = "\0";
                date_as_string(current->date, date_str,  10);
                
                snprintf(sales_string + strlen(sales_string), estimated_length, (current->next==NULL) ?"[%s, %s, %d]" : "[%s, %s, %d], ", date_str, current->item->product_code, current->quantity);
                current = current->next;
            }
            snprintf(sales_string + strlen(sales_string),estimated_length, " )");
            printf("%s\n", sales_string);
        }
        
    }
    
    Sales_Volume* apply_sales(Sales* sales, FILE* log){
        
        //optimisation decision - less processing/data overhead required to determine highest sales volume of all successful transactions and return in apply_sales_to_inventory().
        //Bugfix - initialised integers to avoid undefined behaviour
        Date* highest_volume_date;
        int highest_volume = INT32_MIN;
        int highest_volume_spend = 0;
        int failed_transactions = 0;
        
        Date* current_volume_date;
        int current_volume = 0;
        int current_volume_spend = 0;
        
        SNode* current = sales->first;
        while(current!=NULL){
            
            int new_quantity = current->item->quantity - current->quantity;
            
            //Do not process transaction if there is not enough stock
            if (new_quantity < 0){
                failed_transactions = failed_transactions + 1;
                if (log != NULL){
                    fprintf(log, "Can't process transaction %.2d/%.2d/%.4d, %s, %d: ONLY %d REMAINING.\n", current->date.dayOfMonth, current->date.month, current->date.year, current->item->product_code, current->quantity, current->item->quantity);
                }
            }else{
                
                //there is enough stock, apply transaction
                
                //BUT FIRST - update measure of sales volume and keep record of highest date
                if (datecmp(current_volume_date, &(current->date)) != 0){
                    //sale is for a different date, starting a new running count
                    
                    //BUT FIRST - is the current a new record?
                    if (current_volume > highest_volume){
                        //Found new highest sales volume
                        highest_volume = current_volume;
                        highest_volume_date = current_volume_date;
                        highest_volume_spend = current_volume_spend;
                    }
                    current_volume_date = &(current->date);
                    current_volume = current->quantity;
                    current_volume_spend = current->quantity * current->item->price_per_unit;
                    
                }else{
                    //sale is for the same date, increment
                    current_volume = current_volume + current->quantity;
                    current_volume_spend = current_volume_spend +(current->quantity * current->item->price_per_unit);
                }
                
                //actually update the stock level
                current->item->quantity = new_quantity;
            }
            
            current = current->next;
        }
        
        //return highest sales volume stats
        Sales_Volume* performance_record = sales_volume_new();
        performance_record->date = highest_volume_date;
        performance_record->volume = highest_volume;
        performance_record->pence_spent = highest_volume_spend;
        performance_record->failed_transactions = failed_transactions;
        return performance_record;
    }
    
    Sales_Volume* sales_volume_new(){
        //Allocate memory for a new sales volume (so it can be referenced outside the scope of the initialising code)
        Sales_Volume* sales_volume = (Sales_Volume*)malloc(sizeof(Sales_Volume));
        return sales_volume;
    }