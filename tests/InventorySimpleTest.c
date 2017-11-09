/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InventorySimpleTest.c
 * Author: Hakeem
 *
 * Created on 08 November 2017, 23:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Inventory.h"
/*
 * Simple C Test Suite
 * 
 * 
 * Below is boilerplate test code.
    void testCanXXXXX(char* testname) {
        printf("\n****************\n%s\n****************\n", testname);

        char* errormessage = "Not Implemented.";



        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=%s\n", testname, errormessage);
    }
 * 
 * */

void testCanAddItems(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    
    StockItem* item = item_new("resistor, code, 10, 99, 10R1\n");
    
    int expected_length = 0;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 0, got %d\n", testname, inventory_length(inventory)); 
    }
    
    inventory_add(inventory, item);
    
    expected_length = 1;
    if (inventory_length(inventory) != expected_length) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 1, got %d\n", testname, inventory_length(inventory)); 
    }
}

void testCanPrintInventory(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    
    int expected_length = 0;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 0, got %d\n", testname, inventory_length(inventory)); 
    }
    
    StockItem* item = item_new("resistor, code1, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code2, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code3, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    
    expected_length = 3;
    if (inventory_length(inventory) != expected_length) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 1, got %d\n", testname, inventory_length(inventory)); 
    }
    
    char* expected_string = "( [resistor, code1, 10, 99, 10R1], [resistor, code2, 10, 99, 10R1], [resistor, code3, 10, 99, 10R1] )";
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    if (strncmp(expected_string, inventory_string, strlen(expected_string)) != 0) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    
}

void testCanLoadInventory(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    
    int expected_length = 0;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 0, got %d\n", testname, inventory_length(inventory)); 
    }
    
    FILE* fd = fopen("testdata.txt", "r");
    load_inventory(fd, inventory);
    fclose(fd);
    
    expected_length = 10;
    if (inventory_length(inventory) != expected_length) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 1, got %d\n", testname, inventory_length(inventory)); 
    }
    
    char* expected_string = "( [resistor, RES_1R0, 41, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 585, 85, 300uF], [capacitor, CAP_150pF, 585, 85, 300uF], [diode, 1N4004,  194, 6], [diode, 1N4148,  201, 5], [transistor, OC44,     57, 50, PNP], [transistor, 2N2369A,  37, 18, NPN], [IC, LF356,  1, 45,  \"JFET op-amp\"] )";
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    if (strncmp(expected_string, inventory_string, strlen(expected_string))) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    
}


int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% InventorySimpleTest\n");
    printf("%%SUITE_STARTED%%\n");
    //SUITE START***********************************************************
    
    clock_t start, end;
    double duration;
    double total_duration = 0.0f;
    char* testname;
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanAddItems";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanAddItems(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (InventorySimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanPrintInventory";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanPrintInventory(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (InventorySimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanLoadInventory";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanLoadInventory(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (InventorySimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    
    //SUITE FINISH**********************************************************

    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
