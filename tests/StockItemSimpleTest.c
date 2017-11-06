/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   StockItemSimpleTest.c
 * Author: Hakeem
 *
 * Created on 05 November 2017, 16:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "StockItem.h"

/*
 * Simple C Test Suite
 */

void testCanCreateFromLine() {
    printf("StockItemSimpleTest testCanCreateFromLine\n");
    
    StockItem* test = new_item("resistor, code, 10, 99, 10R1\n");
    char* expected = "10R1";
    char* testVal = test->description.resistance.original;
    int asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "resistor";
    testVal = test->type;
    asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "code";
    testVal = test->product_code;
    asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->quantity == 10) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 10, test->quantity);
    }
    
    asExpected = (test->price_per_unit == 99) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 99, test->price_per_unit);
    }   
}

void testCanNormaliseResistances(){
    printf("StockItemSimpleTest testCanCreateFromLine\n");
    
    StockItem* test = new_item("resistor, code, 10, 99, 10R1\n");
    char* expected = "10R1";
    char* testVal = test->description.resistance.original;
    int asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.resistance.normalised_resistance == 10.1f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 10.1f, test->description.resistance.normalised_resistance);
    }
    
    test = new_item("resistor, code, 10, 99, 60K4\n");
    expected = "60K4";
    testVal = test->description.resistance.original;
    asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.resistance.normalised_resistance == 60400.0f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 60400.0f, test->description.resistance.normalised_resistance);
    }
    
    test = new_item("resistor, code, 10, 99, 10M5\n");
    expected = "10M5";
    testVal = test->description.resistance.original;
    asExpected = strcmp(expected, testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.resistance.normalised_resistance == 10500000.0f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 10500000.0f, test->description.resistance.normalised_resistance);
    }
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% StockItemSimpleTest\n");
    printf("%%SUITE_STARTED%%\n");

    clock_t start, end;
    double duration;
    double total_duration = 0.0f;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanCreateFromLine (StockItemSimpleTest)\n");
    testCanCreateFromLine();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanCreateFromLine (StockItemSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanCreateFromLine (StockItemSimpleTest)\n");
    testCanNormaliseResistances();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanCreateFromLine (StockItemSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;

    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
