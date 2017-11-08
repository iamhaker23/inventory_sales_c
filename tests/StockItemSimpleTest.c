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
#include <float.h>

#include "StockItem.h"

/*
 * Simple C Test Suite
 * 
 * Known bugs:
 *      StockItem created from line with no EOL (\n) will overflow and read adjacent memory
 * 
 */

void testCanCreateFromLine() {
    printf("StockItemSimpleTest testCanCreateFromLine\n");
    
    StockItem* test = item_new("resistor, code, 10, 99, 10R1\n");
    
    char* expected = "10R1";
    char* testVal = test->description.resistance.original;
    int asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "resistor";
    testVal = test->type;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "code";
    testVal = test->product_code;
    asExpected = strncmp(expected, testVal, strlen(expected));
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
    
    
            
    test = item_new("diode, 1N4148,  201, 5\n");
    //Test all variances of the union equal NULL when not set
    asExpected = (test->description.ic_desc == NULL)? 0 : -1;
    asExpected = (test->description.resistance.original == NULL)? asExpected : -1;
    asExpected = (test->description.capacitance.original == NULL)? asExpected : -1;
    asExpected = (test->description.transistor_config == NULL)? asExpected : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "diode";
    testVal = test->type;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "1N4148";
    testVal = test->product_code;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->quantity == 201) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 10, test->quantity);
    }
    
    asExpected = (test->price_per_unit == 5) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 99, test->price_per_unit);
    }
    
    //NOTE: this test includes tab characters -> transistor,\tAC125,\t13,\t35,\tPNP\n
    test = item_new("transistor,	AC125,	13,	35,	PNP\n");
    expected = "PNP";
    testVal = test->description.transistor_config;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "transistor";
    testVal = test->type;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "AC125";
    testVal = test->product_code;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->quantity == 13) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 10, test->quantity);
    }
    
    asExpected = (test->price_per_unit == 35) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 99, test->price_per_unit);
    }
    
    test = item_new("capacitor, CAP_1500nF, 796, 68, 1500nF\n");
    expected = "1500nF";
    testVal = test->description.capacitance.original;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->description.capacitance.normalised_capacitance == 0.000001500f)? 0 : 1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 0.000001500f, test->description.capacitance.normalised_capacitance);
    }
    
    expected = "capacitor";
    testVal = test->type;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "CAP_1500nF";
    testVal = test->product_code;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->quantity == 796) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 10, test->quantity);
    }
    
    asExpected = (test->price_per_unit == 68) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 99, test->price_per_unit);
    }
    
    
    test = item_new(    "IC, NE555,  8, 17,  \"Timer\"\n");
    expected = "Timer";
    testVal = test->description.ic_desc;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "IC";
    testVal = test->type;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    expected = "NE555";
    testVal = test->product_code;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    
    asExpected = (test->quantity == 8) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 10, test->quantity);
    }
    
    asExpected = (test->price_per_unit == 17) ? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %d \ngot\n\t %d.\n", 99, test->price_per_unit);
    }
}

void testCanNormaliseResistances(){
    printf("StockItemSimpleTest testCanNormaliseResistances\n");
    
    StockItem* test = item_new("resistor, code, 10, 99, 10R1\n");
    
    char* expected = "10R1";
    char* testVal = test->description.resistance.original;
    int asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.resistance.normalised_resistance == 10.1f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 10.1f, test->description.resistance.normalised_resistance);
    }
    
    test = item_new("resistor, code, 10, 99, 60K4\n");
    expected = "60K4";
    testVal = test->description.resistance.original;
    asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.resistance.normalised_resistance == 60400.0f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 60400.0f, test->description.resistance.normalised_resistance);
    }
    
    test = item_new("resistor, code, 10, 99, 10M5\n");
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

void testCanNormaliseCapacitance(){
    printf("StockItemSimpleTest testCanNormaliseCapacitance\n");
    
    StockItem* test = item_new("capacitor, CAP_1500nF, 796, 68, 1500nF\n");
    char* expected = "1500nF";
    char* testVal = test->description.capacitance.original;
    int asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.capacitance.normalised_capacitance == 0.000001500f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %f \ngot\n\t %f.\n", 0.000001500f, test->description.capacitance.normalised_capacitance);
    }
    
    test = item_new("capacitor, CAP_130uF, 503, 93, 130uF\n");
    expected = "130uF";
    testVal = test->description.capacitance.original;
    asExpected = asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.capacitance.normalised_capacitance == 0.000130f)? 0 : -1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %lf \ngot\n\t %lf.\n", expected, test->description.capacitance.normalised_capacitance);
    }
    
    test = item_new("capacitor, CAP_15pF, 448, 8, 15pF\n");
    expected = "15pF";
    testVal = test->description.capacitance.original;
    asExpected = asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
    }
    asExpected = (test->description.capacitance.normalised_capacitance == 0.000000000015f)? 0 : -1;
                                                                          
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %lf \ngot\n\t %lf.\n", 0.000000000015f, test->description.capacitance.normalised_capacitance);
    }
    
}

void testCanStringifyStockItem(){
    printf("StockItemSimpleTest testCanStringifyStockItem\n");
    
    StockItem* test = item_new("capacitor, CAP_1500nF, 796, 68, 1500nF\n");
    char* expected = "capacitor, CAP_1500nF, 796, 68, 1500nF";
    int buffer_length = stockitem_estimate_required_buffer(test);
    char testVal[buffer_length];
    stockitem_as_string(test, (char*)testVal, buffer_length);
    int asExpected = strcmp(expected, (char*)testVal);
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanStringifyStockItem (StockItemSimpleTest) message=failed to stringify StockItem, expected\n\t %s \ngot\n\t %s \nfrom \n\t%s.\n", expected, testVal, test->original_line_def);
    }
}
    
void testCanDetermineCheaperStockItem(){
    printf("StockItemSimpleTest testCanDetermineCheaperStockItem\n");
    
    StockItem* test = item_new("capacitor, CAP_1500nF, 796, 68, 1500nF\n");
    StockItem* test2 = item_new("capacitor, CAP_1500nF, 796, 100, 1500nF\n");
    char* expected = "1500nF";
    int testa = test->price_per_unit;
    int testb = test2->price_per_unit;
    
    int asExpected = (testa < testb)?0:-1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanDetermineCheaperStockItem (StockItemSimpleTest) message=testa (%d) is not cheaper than testb(%d)", testa, testb);
    }
    
    //test is cheaper than test2
    asExpected = (stockitem_is_cheaper_than(test, test2)==1)?0:-1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanDetermineCheaperStockItem (StockItemSimpleTest) message=Could not determine cheaper stock item, %d -> %d.\n", testa, testb);
    }
    
    //test2 is not cheaper than test
    asExpected = (stockitem_is_cheaper_than(test2, test)==-1)?0:-1;
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanDetermineCheaperStockItem (StockItemSimpleTest) message=Could not determine cheaper stock item, %d -> %d.\n", testb, testa);
    }
    
}

void testCanDetermineValidItem(){
    StockItem* test = item_new("resistor, code, 10, 99, 10R1\n");
    char* expected = "10R1";
    char* testVal = test->description.resistance.original;
    int asExpected = asExpected = strncmp(expected, testVal, strlen(expected));
    if (asExpected != 0){
        printf("%%TEST_FAILED%% time=0 testname=testCanCreateFromLine (StockItemSimpleTest) message=failed to create StockItem, expected\n\t %s \ngot\n\t %s.\n", expected, testVal);
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
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanNormaliseCapacitance (StockItemSimpleTest)\n");
    testCanNormaliseCapacitance();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanNormaliseCapacitance (StockItemSimpleTest) \n", duration);
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanStringifyStockItem (StockItemSimpleTest)\n");
    testCanStringifyStockItem();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanStringifyStockItem (StockItemSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    printf("%%TEST_STARTED%% testCanDetermineCheaperStockItem (StockItemSimpleTest)\n");
    testCanDetermineCheaperStockItem();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f testCanDetermineCheaperStockItem (StockItemSimpleTest) \n", duration);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    

    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
