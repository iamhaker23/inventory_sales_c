/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdint.h>

#include "Sales.h"
#include "Inventory.h"

    Sales* sales_ledger_new(){
        Sales* new_list = (Sales*)malloc(sizeof(Sales));
        if (new_list == NULL)
        {
          fprintf(stderr, "Error: Unable to allocate memory in list_new()\n");

          exit(EXIT_FAILURE);
        }

        new_list->first = NULL;
        new_list->last  = NULL;
        new_list->length = 0;

        return new_list; 
    }

    int sales_ledger_length(Sales* list){
        return list->length;
    }

    void sales_ledger_add(Sales* list, StockItem* item, Date date, int quantity){
            SNode* tmp = (SNode*)malloc(sizeof(SNode));
    
            if (tmp == NULL){
                fprintf(stderr, "Error: Unable to allocate memory in list_tail_insert()\n");
                exit(EXIT_FAILURE);
            }

            tmp->item = item;
            tmp->date = date;
            tmp->quantity = quantity;
            tmp->next = NULL;
            tmp->previous = list->last;

            if(list->last == NULL){
                list->last = list->first = tmp;
            }else{
                //The last element of the list is now tmp, and whatever WAS the last element now points to tmp
                list->last = list->last->next = tmp;
            }

            list->length=list->length+1;
    }

    void sales_ledger_empty(Sales* list){
        SNode* node;
    
        while(list->first != NULL){
            SNode* node = list->first;
            list->first = node->next;
            free(node);
        }

        list->last = NULL;
    }

    
    void sales_ledger_sort(Sales* list, int ascending_flag){
        if(list->first != list->last){
            //list contains more than one item
            int sorted;
            if (ascending_flag == 1){
                do{
                    sorted = 1;
                    for(SNode* node = list->first; node->next != NULL; node=node->next){
                        if (datecmp(&(node->date), &(node->next->date)) > 0 ){
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

                           sorted = 0;
                        }
                    }
                }while(!sorted);
            }else{
                do{
                    sorted = 1;
                    for(SNode* node = list->first; node->next != NULL; node=node->next){
                        if (datecmp(&(node->date), &(node->next->date)) < 0 ){
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

                           sorted = 0;

                        }
                    }
                }while(!sorted);
            }
        }
    }

    void sales_ledger_gc(Sales* list){
        sales_ledger_empty(list);
        free(list);
    }
    
    int datecmp(Date* a, Date* b){
        int output = 0;
        
        //bias NULL to represent "earliest possible date"
        if (a == NULL){
            return -1;
        }
        if (b == NULL){
            return 1;
        }
        
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
            size_t line_buff_size = 100;
            size_t read = 0;
            char line[line_buff_size];
            char* line_ptr = line;

            while((read = (getline(&line_ptr, &line_buff_size, fd))) && read!=-1 ){
                
                if (line[0] == '\n' || line[0] == '\r'){
                    continue;
                }
                
                char quantity[20] = "\0";
                char date[20] = "\0";
                char code[20] = "\0";
                
                int index = 0;
                const int NUM_FIELDS = 3;
                const int MAX_FIELD_LENGTH = 20;

                for (int i = 1; i <= NUM_FIELDS; i++){
                    char tmp = line[index++];
                    if (tmp != '\n' && tmp != '\r'){
                        while (tmp != ',' && tmp != '\n' && tmp != '\r'){
                            //omit space, tab and quotes
                            if (tmp != ' ' && tmp != '\t' && tmp != '"'){
                                switch(i){
                                   case(1):
                                       snprintf(date, MAX_FIELD_LENGTH, "%s%c", date, tmp);
                                       tmp = line[index++];
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(date, MAX_FIELD_LENGTH, "%s%c", date, '\0');
                                       }
                                       break;
                                   case(2):
                                       snprintf(code, MAX_FIELD_LENGTH, "%s%c", code, tmp);
                                       tmp = line[index++];
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(code, MAX_FIELD_LENGTH, "%s%c", code, '\0');
                                       }
                                       break;
                                   case(3):
                                       snprintf(quantity, MAX_FIELD_LENGTH, "%s%c", quantity, tmp);
                                       tmp = line[index++];
                                       if (tmp == ',' || tmp == '\n' || tmp == '\r'){
                                            snprintf(quantity, MAX_FIELD_LENGTH, "%s%c", quantity, '\0');
                                       }
                                       break;
                                   default:
                                       tmp = line[index++];
                                       break;
                                }
                            }else{
                                tmp = line[index++];
                            }

                        }
                    }else{
                        if (index == 1){
                            //The line starts \r\n or \r or \n (e.g. empty line)
                        }
                    }
                }
                
                
                StockItem* item = get_item_by_product_code(inventory, code);
                if (item != NULL){
                    
                    Date date_obj = date_malloc(date);
                    int quantity_obj = int_malloc(quantity);
                    sales_ledger_add(list, item, date_obj, quantity_obj);
                }else{
                    fprintf(stderr, "Could not process transaction for %s: Item doesn't exist.\n", code);
                }
            }

        }else{
            printf("Error: NULL file provided.");
            exit(EXIT_FAILURE);
        }
    }
    
    Date date_malloc(char* date){
        //strictly converts a 10 character DD/MM/YYYY string
        const char delimiter = '/';
        
        if (strlen(date) != 10 || date[2] != '/' || date[5] != '/'){
            fprintf(stderr, "Could not convert date: %s.\n", date);
            exit(EXIT_FAILURE);
        }
        
        Date* output = (Date*)malloc(sizeof(Date));
       
        char part[4] ="0000";
        snprintf(part, 5, "00%c%c", date[0], date[1]);
        int dayOfMonth = atoi(part);
        
        snprintf(part, 5, "00%c%c", date[3], date[4]);
        int month = atoi(part);
        
        snprintf(part, 5, "%c%c%c%c", date[6], date[7], date[8], date[9]);
        int year = atoi(part);
        
        output->dayOfMonth = dayOfMonth;
        output->month = month;
        output->year = year;
        
        return *output;
    }
    
    void date_as_string(Date date, char* date_str, int buff_size){
        if (buff_size < 10){
            fprintf(stderr, "Could not load datestring into %d buffer.\n", buff_size);
            exit(EXIT_FAILURE);
        }
        snprintf(date_str, 11, "%0.2d/%0.2d/%0.4d", date.dayOfMonth, date.month, date.year);
    }
    
    int sales_ledger_estimate_required_buffer(Sales* sales){
        return sales->length*50;
    }
    
    void sales_ledger_as_string(Sales* sales, char* sales_string, int estimated_length){
        
        //undefined behaviuour if sales_string is not empty.

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
    
    Sales_Volume* apply_sales_to_inventory(Sales* sales, Inventory* inventory, FILE* log){
        
        //optimisation decision - less processing/data overhead required to determine highest sales volume of all successful transactions and return in apply_sales_to_inventory().
        Date* highest_volume_date;
        int highest_volume = INT32_MIN;
        int highest_volume_spend;
        
        Date* current_volume_date;
        int current_volume;
        int current_volume_spend;
        
        SNode* current = sales->first;
        while(current!=NULL){
            
            int new_quantity = current->item->quantity - current->quantity;
            
            if (new_quantity < 0){
                fprintf(stderr, "Can't process transaction %0.2d/%0.2d/%0.4d, %s, %d: ONLY %d REMAINING.\n", current->date.dayOfMonth, current->date.month, current->date.year, current->item->product_code, current->quantity, current->item->quantity);
                if (log != NULL){
                    fprintf(log, "Can't process transaction %0.2d/%0.2d/%0.4d, %s, %d: ONLY %d REMAINING.\n", current->date.dayOfMonth, current->date.month, current->date.year, current->item->product_code, current->quantity, current->item->quantity);
                }
            }else{
                
                //transaction was successful, so apply as such
                
                if (datecmp(current_volume_date, &(current->date)) != 0){
                    //different date, starting a new count
                    if (current_volume > highest_volume){
                        highest_volume = current_volume;
                        highest_volume_date = current_volume_date;
                        highest_volume_spend = current_volume_spend;
                    }
                    current_volume_date = &(current->date);
                    current_volume = current->quantity;
                    current_volume_spend = current->quantity * current->item->price_per_unit;
                }else{
                    //same date, increment
                    current_volume = current_volume + current->quantity;
                    current_volume_spend = current_volume_spend +(current->quantity * current->item->price_per_unit);
                }
                
                current->item->quantity = new_quantity;
            }
            
            current = current->next;
        }
        Sales_Volume* performance_record = sales_volume_new();
        performance_record->date = *highest_volume_date;
        performance_record->volume = highest_volume;
        performance_record->pence_spent = highest_volume_spend;
        return performance_record;
    }
    
    Sales_Volume* sales_volume_new(){
        Sales_Volume* sales_volume = (Sales_Volume*)malloc(sizeof(Sales_Volume));
        return sales_volume;
    }