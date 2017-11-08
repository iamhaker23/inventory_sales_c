/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LinkedListSimpleTest.c
 * Author: Hakeem
 *
 * Created on 04 November 2017, 14:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include <time.h>

/*
 * "Simple C Test" Suite
 * 
 * To fail a test: printf("%%TEST_FAILED%% time=0 testname=test2 (LinkedListSimpleTest) message=error message sample\n");
 */

const int NUMBER_OF_ELEMENTS = 1000;

void testNewList() {
    
    printf("\n*****************************************\nLinkedListSimpleTest test new_list()\n");
    List* list = list_new();

    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        list_head_insert(list, get_data_type_int(rand()%100));
    }
    
    if (list_length(list) == NUMBER_OF_ELEMENTS){
        printf("List length as expected: %d\n", NUMBER_OF_ELEMENTS);
    }else{
        printf("%%TEST_FAILED%% time=0 testname=testNewList (LinkedListSimpleTest) message=Expected list length of %d but got %d.\n", NUMBER_OF_ELEMENTS, list_length(list));
    }
    
    list_gc(list);
}

void testListPopHead(){
    
    printf("\n*****************************************\nLinkedListSimpleTest test list_pop_head()\n");
    List* list = list_new();

    for (int i = 0; i != NUMBER_OF_ELEMENTS; i++)
    {
       //Will add 0..NUMBER_OF_ELEMENTS in reverse order
       list_head_insert(list, get_data_type_int(i));
    }
    
    for(int j = 1; j <= NUMBER_OF_ELEMENTS; j++){
        
        
        int poppedHead = list_pop_head(list).int_val;
        //List contains NUMBER_OF_ELEMENTS..0 collected head first, e.g. NUMBER_OF_ELEMENTS..0
        int expectedValue = NUMBER_OF_ELEMENTS - j;
        
        int lengthAfterPop = list_length(list);
        int expectedLength = (NUMBER_OF_ELEMENTS-j);
        
        if(poppedHead != expectedValue){
            printf("%%TEST_FAILED%% time=0 testname=testListPopHead (LinkedListSimpleTest) message=Expected value of %d but got %d.\n", expectedValue, poppedHead);
        }
        
        if (lengthAfterPop == expectedLength){
            //printf("List length as expected after pop: %d \n", lengthAfterPop);
        }else{
            printf("%%TEST_FAILED%% time=0 testname=testListPopHead (LinkedListSimpleTest) message=Expected list length of %d but got %d.\n", expectedLength, lengthAfterPop);
        }
    }
    
    
    
}

void testListPopTail(){
    
    printf("\n*****************************************\nLinkedListSimpleTest test list_pop_tail()\n");
    List* list = list_new();

    for (int i = 0; i != NUMBER_OF_ELEMENTS; i++)
    {
       //Will add 0..NUMBER_OF_ELEMENTS in reverse order
       list_head_insert(list, get_data_type_int(i));
    }
    
    for(int j = NUMBER_OF_ELEMENTS; j > 0; j--){
        
        
        int poppedTail = list_pop_tail(list).int_val;
        //List contains NUMBER_OF_ELEMENTS..0 collected tail first, e.g. 0..NUMBER_OF_ELEMENTS
        int expectedValue = NUMBER_OF_ELEMENTS - j;
        
        int lengthAfterPop = list_length(list);
        int expectedLength = j-1;
        
        if(poppedTail != expectedValue){
            printf("%%TEST_FAILED%% time=0 testname=testListPopTail (LinkedListSimpleTest) message=Expected value of %d but got %d.\n", expectedValue, poppedTail);
        }
        
        if (lengthAfterPop == expectedLength){
            //printf("List length as expected after pop: %d \n", lengthAfterPop);
        }else{
            printf("%%TEST_FAILED%% time=0 testname=testListPopTail (LinkedListSimpleTest) message=Expected list length of %d but got %d.\n", expectedLength, lengthAfterPop);
        }
    }
    
}

void testListGC(){
    printf("\n*****************************************\nLinkedListSimpleTest test list_gc()\n");
    List* list = list_new();

    for (int i = 0; i != NUMBER_OF_ELEMENTS; i++)
    {
       //Will add 0..NUMBER_OF_ELEMENTS in reverse order
       list_head_insert(list, get_data_type_int(i));
    }
    
    int listSize = list_memory_size(list);
    int expectedListSize = sizeof(Node) * list_length(list);
    
    if (listSize == expectedListSize){
        //printf("Object size as expected: %d\n", listSize);
    }else{
        printf("%%TEST_FAILED%% time=0 testname=testListGC (LinkedListSimpleTest) message=Expected list length of %d but got %d.\n", expectedListSize, listSize);
    }
    
    list_gc(list);
    listSize = list_memory_size(list);
    
    if (listSize == 0){
        //printf("Object size after gc as expected: %d\n", listSize);
    }else{
        printf("%%TEST_FAILED%% time=0 testname=testListGC (LinkedListSimpleTest) message=Expected list length of %d but got %d.\n", 0, listSize);
    }
    
}

void testListAsString(){
    printf("\n*****************************************\nLinkedListSimpleTest test list_as_string()\n");
    List* list = list_new();

    for (int i = 0; i != NUMBER_OF_ELEMENTS; i++)
    {
       //Will add 0..NUMBER_OF_ELEMENTS in reverse order
       list_head_insert(list, get_data_type_int(i));
    }
    
    int string_buffer_size = list_estimate_required_buffer(list);
    char listAsString[string_buffer_size];
    //snprintf(listAsString, 512, list_as_string(list));
    list_as_string(list, listAsString, string_buffer_size);
    //if(strcmp(listAsString, "( 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 )") == 0){
    printf("List as string as expected: %s\n", listAsString);
    //}else{
        //printf("%%TEST_FAILED%% time=0 testname=testListAsString (LinkedListSimpleTest) message=String not as expected: %s.\n", listAsString);
    //}
}

void testListSort(){
    printf("*****************************************\nLinkedListSimpleTest test list_sort()\n");
    List* list = list_new();

    for (int i = 0; i != NUMBER_OF_ELEMENTS; i++)
    {
       //Will add 0..NUMBER_OF_ELEMENTS in reverse order
       list_head_insert(list, get_data_type_int(rand()%(NUMBER_OF_ELEMENTS*10)));
    }
    int string_buffer_size = list_estimate_required_buffer(list);
    char listAsString[string_buffer_size];
    list_as_string(list, listAsString, string_buffer_size);
    printf("List before sorting: %s\n", listAsString);
    
    list_sort(list, 0, 1);
    
    list_as_string(list, listAsString, string_buffer_size);
    printf("List after sorting (desc): %s\n", listAsString);
    
    
    list_sort(list, 1, 1);
    
    list_as_string(list, listAsString, string_buffer_size);
    printf("List after sorting (asc): %s\n", listAsString);
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% LinkedListSimpleTest\n");
    printf("%%SUITE_STARTED%%\n");
    
    clock_t start, end;
    double duration;
    double total_duration = 0.0f;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testNewList (LinkedListSimpleTest)\n");
    testNewList();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testNewList (LinkedListSimpleTest) \n", duration);
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testListPopHead (LinkedListSimpleTest)\n");
    testListPopHead();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testListPopHead (LinkedListSimpleTest) \n", duration);
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testListPopTail (LinkedListSimpleTest)\n");
    testListPopTail();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testListPopTail (LinkedListSimpleTest) \n", duration);
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testListGC (LinkedListSimpleTest)\n");
    testListGC();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testListGC (LinkedListSimpleTest) \n", duration);
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testListAsString (LinkedListSimpleTest)\n");
    testListAsString();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testListAsString (LinkedListSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testListSort (LinkedListSimpleTest)\n");
    testListSort();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testListSort (LinkedListSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
