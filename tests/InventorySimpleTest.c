/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InventorySimpleTest.c
 * Author: Hakeem
 *
 * Created on 04 November 2017, 14:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inventory.h"
#include "StockItem.h"
#include <time.h>

/*
 * "Simple C Test" Suite
 * 
 */

const int NUMBER_OF_ELEMENTS = 10;

void testCanAddItems(){
    printf("*****************************************InventorySimpleTest testCanAddItems\n");
    
    Inventory* inventory = inventory_new();
    
    int testVal = inventory_count(inventory);
    int expected = 0;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCanLoadFromFile (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", 0, testVal);
    }
    
    StockItem* item = item_new("capacitor, CAP_15pF, 448, 8, 15pF\n");
    inventory_add(inventory, item);
    
    testVal = inventory_count(inventory);
    
    expected = 1;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCanLoadFromFile (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    //cannot add same product code twice!
    inventory_add(inventory, item);
    testVal = inventory_count(inventory);
    expected = 1;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCanLoadFromFile (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
}

void testCanPrintInventoryAsString(){
    printf("*****************************************InventorySimpleTest testCanPrintInventoryAsString\n");
    
    Inventory* inventory = inventory_new();
    
    int testVal = inventory_count(inventory);
    int expected = 0;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCanPrintInventoryAsString (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", 0, testVal);
    }
    
    StockItem* item = item_new("capacitor, CAP_15pF, 448, 8, 15pF\n");
    inventory_add(inventory, item);
    StockItem* item2 = item_new("resistor, code, 10, 99, 10R1\n");
    inventory_add(inventory, item2);
    testVal = inventory_count(inventory);
    
    expected = 2;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCanPrintInventoryAsString (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    char* expectedString = "( [capacitor, CAP_15pF, 448, 8, 15pF], [resistor, code, 10, 99, 10R1] )";
    int buffer_size = inventory_estimate_required_buffer(inventory);
    char buffer[buffer_size];
    inventory_as_string(inventory, buffer, buffer_size);
    
    if (strncmp(expectedString, (char*)buffer, strlen(expectedString)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanPrintInventoryAsString (InventorySimpleTest) message=Expected %sgot\n%s.\n", expectedString, buffer);
    }else{
        printf("Correctly generated string: %s.\n", buffer);
    }
    
}

void testGetItemByProductCode(){
    printf("*****************************************InventorySimpleTest testGetItemByProductCode\n");
    
    Inventory* inventory = inventory_new();
    
    int testVal = inventory_count(inventory);
    int expected = 0;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testGetItemByProductCode (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", 0, testVal);
    }
    
    StockItem* item = item_new("capacitor, code1, 448, 8, 15pF\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code2, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code3, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code4, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    item = item_new("resistor, code5, 10, 99, 10R1\n");
    inventory_add(inventory, item);
    testVal = inventory_count(inventory);
    
    expected = 5;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testGetItemByProductCode (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    char* code = "code5";
    StockItem* retrieved = get_item_by_product_code(inventory, code);
    if (!(retrieved == item)){
        printf("%%TEST_FAILED%% time=0 testname=testGetItemByProductCode (InventorySimpleTest) message=Expected pointer %d, got %d.\n", (long)item, (long)retrieved);
    }
    
    int itemAsStringLen = stockitem_estimate_required_buffer(retrieved);
    char itemAsString[itemAsStringLen];
    stockitem_as_string(retrieved, itemAsString, itemAsStringLen);
    printf("StockItem with code %s: %s.\n", code, itemAsString);
    code="FAIL";
    retrieved = get_item_by_product_code(inventory, code);
    if (!(retrieved == NULL)){
        printf("%%TEST_FAILED%% time=0 testname=testGetItemByProductCode (InventorySimpleTest) message=Expected pointer NULL, got %d.\n", (long)retrieved);
    }
    
    itemAsStringLen = stockitem_estimate_required_buffer(retrieved);
    itemAsString[itemAsStringLen];
    stockitem_as_string(retrieved, itemAsString, itemAsStringLen);
    printf("StockItem with code %s: %s.\n", code, itemAsString);
    
}

void testCountTypeMatchingDescription(){
    printf("*****************************************InventorySimpleTest testCountTypeMatchingDescription\n");
    
    Inventory* inventory = inventory_new();
    
    int testVal = inventory_count(inventory);
    int expected = 0;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCountTypeMatchingDescription (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    StockItem* item = item_new("transistor,	code1,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code2,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code3,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code4,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code5,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code6,	13,	35,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code7,	13,	35,	NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code8,	13,	35,	NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code9,	13,	35,	NPN\n");
    inventory_add(inventory, item);
    
    testVal = inventory_count(inventory);
    expected = 9;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCountTypeMatchingDescription (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    testVal = count_type_matching_description(inventory, "transistor", "NPN");
    expected = 3;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCountTypeMatchingDescription (InventorySimpleTest) message=Expected NPN transistor count %d, got %d.\n", expected, testVal);
    }
    
    testVal = count_type_matching_description(inventory, "transistor", "PNP");
    expected = 6;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testCountTypeMatchingDescription (InventorySimpleTest) message=Expected PNP transistor count %d, got %d.\n", expected, testVal);
    }
    
}

void testInventorySortByPrice(){
    printf("*****************************************InventorySimpleTest testInventorySortByPrice\n");
    
    Inventory* inventory = inventory_new();
    
    int testVal = inventory_count(inventory);
    int expected = 0;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testInventorySortByPrice (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    StockItem* item = item_new("transistor,	code1,	13,	1,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code2,	13,	100,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code3,	13,	67,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code4,	13,	34,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code6,	13,	26,	PNP\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code7,	13,	68,	NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code8,	13,	22,	NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code9,	13,	98,	NPN\n");
    inventory_add(inventory, item);
    item = item_new("transistor,	code10,	13,	105,	PNP\n");
    inventory_add(inventory, item);
    
    testVal = inventory_count(inventory);
    expected = 9;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testInventorySortByPrice (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
    char* expectedString = "( [transistor,	code1,	13,	1,	PNP], [transistor,	code2,	13,	100,	PNP], [transistor,	code3,	13,	67,	PNP], [transistor,	code4,	13,	34,	PNP], [transistor,	code6,	13,	26,	PNP], [transistor,	code7,	13,	68,	NPN], [transistor,	code8,	13,	22,	NPN], [transistor,	code9,	13,	98,	NPN], [transistor,	code10,	13,	105,	PNP] )";
    int buffer_size = inventory_estimate_required_buffer(inventory);
    char buffer[buffer_size];
    inventory_as_string(inventory, buffer, buffer_size);
    
    if (strncmp(expectedString, (char*)buffer, strlen(expectedString)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=testInventorySortByPrice (InventorySimpleTest) message=Expected presort \n%s\ngot\n%s.\n", expectedString, buffer);
    }else{
        printf("Correctly generated string: %s.\n", buffer);
    }
    
    inventory_sort_by_price(inventory, 1);
    
    expectedString = "( [transistor,	code1,	13,	1,	PNP], [transistor,	code8,	13,	22,	NPN], [transistor,	code6,	13,	26,	PNP], [transistor,	code4,	13,	34,	PNP], [transistor,	code3,	13,	67,	PNP], [transistor,	code7,	13,	68,	NPN], [transistor,	code9,	13,	98,	NPN], [transistor,	code2,	13,	100,	PNP], [transistor,	code10,	13,	105,	PNP] )";
    buffer_size = inventory_estimate_required_buffer(inventory);
    buffer[buffer_size];
    inventory_as_string(inventory, buffer, buffer_size);
    
    if (strncmp(expectedString, (char*)buffer, strlen(expectedString)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=testInventorySortByPrice (InventorySimpleTest) message=Expected postsort \n%sgot\n%s.\n", expectedString, buffer);
    }else{
        printf("Correctly generated string: %s.\n", buffer);
    }
    
    inventory_sort_by_price(inventory, 0);
    
    expectedString = "( [transistor,	code10,	13,	105,	PNP], [transistor,	code2,	13,	100,	PNP], [transistor,	code9,	13,	98,	NPN], [transistor,	code7,	13,	68,	NPN], [transistor,	code3,	13,	67,	PNP], [transistor,	code4,	13,	34,	PNP], [transistor,	code6,	13,	26,	PNP], [transistor,	code8,	13,	22,	NPN], [transistor,	code1,	13,	1,	PNP] )";
    buffer_size = inventory_estimate_required_buffer(inventory);
    buffer[buffer_size];
    inventory_as_string(inventory, buffer, buffer_size);
    
    if (strncmp(expectedString, (char*)buffer, strlen(expectedString)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=testInventorySortByPrice (InventorySimpleTest) message=Expected postsort \n%sgot\n%s.\n", expectedString, buffer);
    }else{
        printf("Correctly generated string: %s.\n", buffer);
    }
    
}

void testLoadInventoryFromFile(){
    
    printf("*****************************************InventorySimpleTest testLoadInventoryFromFile\n");
    
    Inventory* inventory = inventory_new();
    
    FILE* file = fopen("inventory.txt", "r");
    load_inventory(file, inventory);
    fclose(file);
    
    int testVal = inventory_count(inventory);
    int expected = 304;
    if (testVal != expected){
        printf("%%TEST_FAILED%% time=0 testname=testLoadInventoryFromFile (InventorySimpleTest) message=Expected inventory count %d, got %d.\n", expected, testVal);
    }
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% InventorySimpleTest\n");
    printf("%%SUITE_STARTED%%\n");
    
    clock_t start, end;
    double duration;
    double total_duration = 0.0f;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanAddItems (InventorySimpleTest)\n");
    testCanAddItems();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanAddItems (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanPrintInventoryAsString (InventorySimpleTest)\n");
    testCanPrintInventoryAsString();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanPrintInventoryAsString (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testGetItemByProductCode (InventorySimpleTest)\n");
    testGetItemByProductCode();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testGetItemByProductCode (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCountTypeMatchingDescription (InventorySimpleTest)\n");
    testCountTypeMatchingDescription();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCountTypeMatchingDescription (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testInventorySortByPrice (InventorySimpleTest)\n");
    testInventorySortByPrice();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testInventorySortByPrice (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testLoadInventoryFromFile (InventorySimpleTest)\n");
    testLoadInventoryFromFile();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testLoadInventoryFromFile (InventorySimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
