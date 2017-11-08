/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sales.h"

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

    void sales_ledger_tail_insert(Sales* list, StockItem* item, Date* date, int* quantity){
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
                        if (datecmp(node->date, node->next->date) > 0 ){
                           //swap

                           StockItem* tmp_item = node->item ;
                           int* tmp_quantity = node->quantity;
                           Date* tmp_date = node->date;

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
                        if (datecmp(node->date, node->next->date) < 0 ){
                           //swap

                           StockItem* tmp_item = node->item ;
                           int* tmp_quantity = node->quantity;
                           Date* tmp_date = node->date;

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
        
        if ((a->year > b->year) || (a->year == b->year && a->month > b-> month) || (a->year == b->year && a->month == b->month && a->dayOfMonth > b->dayOfMonth)){
            //a is later
            output = 1;
        }else if ((a->year < b->year) || (a->year == b->year && a->month < b-> month) || (a->year == b->year && a->month == b->month && a->dayOfMonth < b->dayOfMonth)){
            output = -1;
        }
        
        return output;
        
    }