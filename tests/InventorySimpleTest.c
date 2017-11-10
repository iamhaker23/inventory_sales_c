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

void testCanPrintCSVInventory(char* testname) {
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
    
    char* expected_string = "\r\nresistor, code1, 10, 99, 10R1\r\nresistor, code2, 10, 99, 10R1\r\nresistor, code3, 10, 99, 10R1\r\n";
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_csv(inventory, inventory_string, estimated_length);
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
    
    char* expected_string = "( [resistor, RES_1R0, 41, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 585, 85, 300uF], [capacitor, CAP_150pF, 585, 85, 300uF], [diode, 1N4004, 194, 6], [diode, 1N4148, 201, 5], [transistor, OC44, 57, 50, PNP], [transistor, 2N2369A, 37, 18, NPN], [IC, LF356, 1, 45, JFETop-amp] )";
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    if (strncmp(expected_string, inventory_string, strlen(expected_string))) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    
}

void testCanSortInventory(char* testname) {
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
    
    char* expected_string = "( [resistor, RES_1R0, 41, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 585, 85, 300uF], [capacitor, CAP_150pF, 585, 85, 300uF], [diode, 1N4004, 194, 6], [diode, 1N4148, 201, 5], [transistor, OC44, 57, 50, PNP], [transistor, 2N2369A, 37, 18, NPN], [IC, LF356, 1, 45, JFETop-amp] )";
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    if (strncmp(expected_string, inventory_string, strlen(expected_string))) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    printf("Presort:%s.\n", inventory_string);
    inventory_sort(inventory, 1);
    
    expected_string = "( [resistor, RES_1R0, 41, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [diode, 1N4148, 201, 5], [diode, 1N4004, 194, 6], [transistor, 2N2369A, 37, 18, NPN], [IC, LF356, 1, 45, JFETop-amp], [transistor, OC44, 57, 50, PNP], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 585, 85, 300uF], [capacitor, CAP_150pF, 585, 85, 300uF] )";
    estimated_length = inventory_estimate_required_buffer(inventory);
    inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    if (strncmp(expected_string, inventory_string, strlen(expected_string))) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    printf("Postsort:%s.\n", inventory_string);
}

void testCanCountStockOfTypeMatchingDescription(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);
    //usage e.g. 
    //count the stock of "transistor" matching description "transistor_config=NPN"
    
    Inventory* inventory = inventory_new();
    
    StockItem* item = item_new("transistor, code1, 10, 97, NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor, code2, 10, 99, NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor, code3, 10, 98, NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor, code4, 10, 99, PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor, code5, 10, 100, PNP\n");
    inventory_add(inventory, item);
    
    int expected_length = 5;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 5, got %d\n", testname, inventory_length(inventory)); 
    }
    
    int actual_count = count_type_matching_description_in_stock(inventory, "transistor", "NPN");
    
    int expected_NPN_count = 3;
    if (actual_count != expected_NPN_count) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected 3, got %d\n", testname, actual_count); 
    }
    
    actual_count = count_type_matching_description_in_stock(inventory, "transistor", "PNP");
    
    int expected_PNP_count = 2;
    if (actual_count != expected_PNP_count) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected 2, got %d\n", testname, actual_count); 
    } 
    
}

void testCanTotalResistanceOfStock(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);
    //usage e.g.
    //count the total resistance of all resistors in stock.
    
    Inventory* inventory = inventory_new();
    
    StockItem* item = item_new("resistor, code1, 10, 97, 10K\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code2, 10, 99, 20K\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code3, 10, 98, 22K\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code4, 10, 99, 100M2\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code5, 10, 100, 1R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code6, 0, 105, 100R1\n");
    inventory_add(inventory, item);
    
    //10000 + 20000 + 22000 + 100200000 + 1.1 = 100252001.1
    
    int expected_length = 6;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 6, got %d\n", testname, inventory_length(inventory)); 
    }
    
    float actual_total_resistance = total_resistance_of_in_stock_resistors(inventory);
    
    float expected_total_resistance = 100252001.1f;
    if (expected_total_resistance != actual_total_resistance) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected 100252001.1, got %f\n", testname, actual_total_resistance); 
    }
    
    item = item_new("resistor, code7, 1, 105, 100R1\n");
    inventory_add(inventory, item);
    
    //10000 + 20000 + 22000 + 100200000 + 1.1 = 100252001.1
    
    expected_length = 7;
    if (inventory_length(inventory) != expected_length) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected length 7, got %d\n", testname, inventory_length(inventory)); 
    }
    
    actual_total_resistance = total_resistance_of_in_stock_resistors(inventory);
    
    expected_total_resistance = 100252101.2f;
    if (expected_total_resistance != actual_total_resistance) {
        printf("%%TEST_FAILED%% time=0 testname=%s (InventorySimpleTest) message=Expected 100252001.1, got %f\n", testname, actual_total_resistance); 
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
    testname = "testCanPrintCSVInventory";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanPrintCSVInventory(testname);
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
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanSortInventory";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanSortInventory(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (InventorySimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanCountStockOfTypeMatchingDescription";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanCountStockOfTypeMatchingDescription(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (InventorySimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanTotalResistanceOfStock";
    printf("%%TEST_STARTED%% %s (InventorySimpleTest)\n", testname);
    testCanTotalResistanceOfStock(testname);
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
