/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "LinkedList.h"

List* list_new(){
    List* new_list = (List*)malloc(sizeof(List));
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

int list_length(List* list){
    return list->length;
}

void list_tail_insert(List* list, union data_type value){
    Node* tmp = (Node*)malloc(sizeof(Node));
    
    if (tmp == NULL){
        fprintf(stderr, "Error: Unable to allocate memory in list_tail_insert()\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->value = value;
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

void list_head_insert(List* list, union data_type value){
    Node* tmp = (Node*)malloc(sizeof(Node));
    
    if (tmp == NULL){
        fprintf(stderr, "Error: Unable to allocate memory in list_head_insert()\n");
        exit(EXIT_FAILURE);
   }
    
   tmp->value = value;
   tmp->next  = list->first;
   tmp->previous = NULL;
   
   if (list->first == NULL)
   {
      list->first = list->last = tmp;
   }
   else
   {
      //The first element of the list is now tmp, and whatever WAS the first element now points to tmp
      list->first = list->first->previous = tmp;
   }
   list->length=list->length+1;
    
}

union data_type list_pop_head(List* list){
    if (list->first == NULL){
        printf("Error: attempted to pop head element from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    
    union data_type value = list->first->value;
    
    Node* head = list->first;
    
    if(list->first == list->last){
        //list becomes empty
        list->first = list->last = NULL;
    }else{
        //only unlink the current head
        list->first = head->next;
        list->first->previous = NULL;
    }
    
    free(head);
    list->length = list->length-1;
    
    if(list->length < 0){
        printf("Error: list length below 0 in list_pop_head()\n");
        exit(EXIT_FAILURE);
    }
    
    return value;
    
}

union data_type list_pop_tail(List* list){
    if (list->last == NULL){
        printf("Error: attempted to pop head element from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    
    union data_type value = list->last->value;
    
    Node* tail = list->last;
    
    if(list->last == list->first){
        //list becomes empty
        list->first = list->last = NULL;
    }else{
        //only unlink the current tail
        list->last = tail->previous;
        list->last->next = NULL;
    }
    
    free(tail);
    list->length = list->length-1;
    
    if(list->length < 0){
        printf("Error: list length below 0 in list_pop_head()\n");
        exit(EXIT_FAILURE);
    }
    
    return value;
    
}

void list_empty(List* list){
    Node* node;
    
    while(list->first != NULL){
        Node* node = list->first;
        list->first = node->next;
        free(node);
    }
    
    list->last = NULL;
}

void list_gc(List* list){
    list_empty(list);
    free(list);
}

void list_sort(List* list, int ascending_flag, int type_sort){
    if(list->first != list->last){
        //list contains more than one item
        int sorted;
        if (ascending_flag == 1){
            do{
                sorted = 1;
                for(Node* node = list->first; node->next != NULL; node=node->next){
                    switch(type_sort){
                        case(1):
                            if (node->value.int_val > node->next->value.int_val ){
                               long tmp = node->value.int_val ;
                               node->value.int_val = node->next->value.int_val ;
                               node->next->value.int_val  = tmp;
                               sorted = 0;
                            }
                            break;
                            
                        case(2):
                            if (node->value.item->price_per_unit > node->next->value.item->price_per_unit ){
                               StockItem* tmp = node->value.item ;
                               node->value.item = node->next->value.item;
                               node->next->value.item  = tmp;
                               sorted = 0;
                            }
                            break;
                            
                        case(3):
                            if (datecmp(node->value.sale->date, node->next->value.sale->date) > 0 ){
                               Record* tmp = node->value.sale ;
                               node->value.sale = node->next->value.sale ;
                               node->next->value.sale  = tmp;
                               sorted = 0;
                            }
                            break;
                        default:
                            printf("Error: expected valid type_sort (1: int_val, 2: StockItem.price, 3:Sales.date) got %d.\n", type_sort);
                            exit(EXIT_FAILURE);
                            break;
                    }
                }
            }while(!sorted);
        }else{
            do{
                sorted = 1;
                for(Node* node = list->first; node->next != NULL; node=node->next){
                    switch(type_sort){
                        case(1):
                            if (node->value.int_val < node->next->value.int_val ){
                               long tmp = node->value.int_val ;
                               node->value.int_val = node->next->value.int_val ;
                               node->next->value.int_val  = tmp;
                               sorted = 0;
                            }
                            break;
                            
                        case(2):
                            if (node->value.item->price_per_unit < node->next->value.item->price_per_unit ){
                               StockItem* tmp = node->value.item ;
                               node->value.item = node->next->value.item;
                               node->next->value.item  = tmp;
                               sorted = 0;
                            }
                            break;
                            
                        case(3):
                            if (datecmp(node->value.sale->date, node->next->value.sale->date) < 0 ){
                               Record* tmp = node->value.sale ;
                               node->value.sale = node->next->value.sale ;
                               node->next->value.sale  = tmp;
                               sorted = 0;
                            }
                            break;
                        default:
                            printf("Error: expected valid type_sort (1: int_val, 2: StockItem.price, 3:Sales.date) got %d.\n", type_sort);
                            exit(EXIT_FAILURE);
                            break;
                    }
                }
            }while(!sorted);
        }
    }
}


void list_fprint(List* list, FILE* fd){
    int buffer_size = list_estimate_required_buffer(list);
    char tmp[buffer_size];
    list_as_string(list, tmp, buffer_size);
    fprintf(fd, tmp);
    fflush(fd);
}

int list_estimate_required_buffer(List* list){
    //assuming max of 10 characters per element.
    int estimate = list->length * 10;
    return estimate;
}

void list_as_string(List* list, char *tmp, int tmp_length){
    
    //stop if the buffer is not large enough
    int est = list_estimate_required_buffer(list);
    if (tmp_length < est ){
        printf("Error: list_as_string() attempted to load %d bytes into %d buffer.\n", est, tmp_length);
        exit(EXIT_FAILURE);
    }
    
    if (list->length == 0){
        snprintf(tmp, sizeof(tmp), "List is empty.");
    }else{
        snprintf(tmp, sizeof(tmp), "( ");
        Node* current = list->first;
        while(current != NULL){
            snprintf(tmp + strlen(tmp), sizeof(tmp), (current->next==NULL) ?"%d" : "%d, ", current->value);
            current = current->next;
        }
        snprintf(tmp + strlen(tmp), sizeof(tmp), " )", list);
    }
}

int list_memory_size(List* list){
    int listSize = 0;
    Node* node = list->first;
    while(node != NULL){
        Node tmp = *node;
        listSize = listSize + sizeof(tmp);
        node = node->next;
    }
    return listSize;
}
union data_type get_data_type_int(long value){
    union data_type obj;
    obj.int_val = value;
    return obj;
}

union data_type get_data_type_stockitem(StockItem* value){
    union data_type obj;
    obj.item = value;
    return obj;
}

union data_type get_data_type_sales(Record* value){
    union data_type obj;
    obj.sale = value;
    return obj;
}
