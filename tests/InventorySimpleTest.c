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
    
    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
