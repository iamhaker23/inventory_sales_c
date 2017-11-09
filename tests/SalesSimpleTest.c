/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SalesSimpleTest.c
 * Author: Hakeem
 *
 * Created on 09 November 2017, 02:43
 */

#include <stdio.h>
#include <stdlib.h>
#include "Sales.h"
#include "Inventory.h"
#include <time.h>

/*
 * Simple C Test Suite
 */

void testCanLoadLedger(char* testname) {
    printf("SalesSimpleTest testCanLoadLedger\n");
    
    Sales* sales = sales_ledger_new();
    
    Inventory* inventory = inventory_new();
    
    FILE* fd = fopen("testdata.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata.txt\n", testname);
    }
    
    load_inventory(fd, inventory);
    fclose(fd);
    
    fd = fopen("testdata_sales.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata_sales.txt\n", testname);
    }
    
    if (sales_ledger_length(sales) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 0, sales_ledger_length(sales));
    }
    
    load_sales_ledger(fd, sales, inventory);
    
    if (sales_ledger_length(sales) != 9){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 9, sales_ledger_length(sales));
    }
    
    
}

void testCanPrintSales(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    Sales* sales = sales_ledger_new();
    
    FILE* fd = fopen("testdata.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata.txt\n", testname);
    }
    
    load_inventory(fd, inventory);
    fclose(fd);
    
    int estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    
    fd = fopen("testdata_sales.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata_sales.txt\n", testname);
    }
    
    if (sales_ledger_length(sales) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 0, sales_ledger_length(sales));
    }
    
    load_sales_ledger(fd, sales, inventory);
    
    if (sales_ledger_length(sales) != 9){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 9, sales_ledger_length(sales));
    }
    
    char* expected_string = "( [20/02/1980, RES_1R0, 6], [21/02/1980, RES_1R0, 8], [21/02/1980, RES_1R0, 1], [22/02/1980, CAP_300uF, 3], [23/02/1980, CAP_300uF, 4], [24/02/1980, CAP_300uF, 8], [24/02/1980, OC44, 5], [24/02/1980, OC44, 6], [31/01/1980, CAP_150pF, 5] )";
    estimated_length = sales_ledger_estimate_required_buffer(sales);
    char* sales_string = (char*)malloc(estimated_length);
    sales_ledger_as_string(sales, sales_string, estimated_length);
    if (strncmp(expected_string, sales_string, strlen(expected_string)) != 0) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, sales_string); 
    }
    
}

void testCanApplySalesAndReportFailures(char* testname) {
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    Sales* sales = sales_ledger_new();
    
    FILE* fd = fopen("testdata.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata.txt\n", testname);
    }
    
    load_inventory(fd, inventory);
    fclose(fd);
    
    fd = fopen("testdata_sales.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata_sales.txt\n", testname);
    }
    
    if (sales_ledger_length(sales) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 0, sales_ledger_length(sales));
    }
    
    load_sales_ledger(fd, sales, inventory);
    
    if (sales_ledger_length(sales) != 9){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 9, sales_ledger_length(sales));
    }
    
    char* expected_string = "( [20/02/1980, RES_1R0, 6], [21/02/1980, RES_1R0, 8], [21/02/1980, RES_1R0, 1], [22/02/1980, CAP_300uF, 3], [23/02/1980, CAP_300uF, 4], [24/02/1980, CAP_300uF, 8], [24/02/1980, OC44, 5], [24/02/1980, OC44, 6], [31/01/1980, CAP_150pF, 5] )";
    int estimated_length = sales_ledger_estimate_required_buffer(sales);
    char* sales_string = (char*)malloc(estimated_length);
    sales_ledger_as_string(sales, sales_string, estimated_length);
    if (strncmp(expected_string, sales_string, strlen(expected_string)) != 0) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, sales_string); 
    }
    
    apply_sales_to_inventory(sales, inventory);
    
    char* exp_code;
    int exp_quantity;
    
    exp_code = "CAP_150pF";
    exp_quantity = 580;
    
    StockItem* item = get_item_by_product_code(inventory, exp_code);
    
    if (item->quantity != exp_quantity){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected %s to have \n%d \nbut got \n%d\n", testname, exp_code, exp_quantity, item->quantity ); 
    }
    
    expected_string="( [resistor, RES_1R0, 26, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 570, 85, 300uF], [capacitor, CAP_150pF, 580, 85, 300uF], [diode, 1N4004, 194, 6], [diode, 1N4148, 201, 5], [transistor, OC44, 46, 50, PNP], [transistor, 2N2369A, 37, 18, NPN], [IC, LF356, 1, 45, JFETop-amp] )";
    estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    
    if (strncmp(inventory_string, expected_string, strlen(expected_string)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    
}

//24/02/1980, 1230p, 19 sales

void testCanApplySalesAndDetermineHighestVolumeDate(char* testname){
    
    printf("\n****************\n%s\n****************\n", testname);

    Inventory* inventory = inventory_new();
    Sales* sales = sales_ledger_new();
    
    FILE* fd = fopen("testdata.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata.txt\n", testname);
    }
    
    load_inventory(fd, inventory);
    fclose(fd);
    
    fd = fopen("testdata_sales.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Could not open testdata_sales.txt\n", testname);
    }
    
    if (sales_ledger_length(sales) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 0, sales_ledger_length(sales));
    }
    
    load_sales_ledger(fd, sales, inventory);
    
    if (sales_ledger_length(sales) != 9){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected sales length %d, got %d.\n", testname, 9, sales_ledger_length(sales));
    }
    
    char* expected_string = "( [20/02/1980, RES_1R0, 6], [21/02/1980, RES_1R0, 8], [21/02/1980, RES_1R0, 1], [22/02/1980, CAP_300uF, 3], [23/02/1980, CAP_300uF, 4], [24/02/1980, CAP_300uF, 8], [24/02/1980, OC44, 5], [24/02/1980, OC44, 6], [31/01/1980, CAP_150pF, 5] )";
    int estimated_length = sales_ledger_estimate_required_buffer(sales);
    char* sales_string = (char*)malloc(estimated_length);
    sales_ledger_as_string(sales, sales_string, estimated_length);
    if (strncmp(expected_string, sales_string, strlen(expected_string)) != 0) { 
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, sales_string); 
    }
    
    Sales_Volume* highest_volume = apply_sales_to_inventory(sales, inventory);
    
    char* exp_code;
    int exp_quantity;
    
    exp_code = "CAP_150pF";
    exp_quantity = 580;
    
    StockItem* item = get_item_by_product_code(inventory, exp_code);
    
    if (item->quantity != exp_quantity){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected %s to have \n%d \nbut got \n%d\n", testname, exp_code, exp_quantity, item->quantity ); 
    }
    
    expected_string="( [resistor, RES_1R0, 26, 1, 1R0], [resistor, RES_10R, 467, 1, 10R], [capacitor, CAP_30uF, 2, 73, 30uF], [capacitor, CAP_300uF, 570, 85, 300uF], [capacitor, CAP_150pF, 580, 85, 300uF], [diode, 1N4004, 194, 6], [diode, 1N4148, 201, 5], [transistor, OC44, 46, 50, PNP], [transistor, 2N2369A, 37, 18, NPN], [IC, LF356, 1, 45, JFETop-amp] )";
    estimated_length = inventory_estimate_required_buffer(inventory);
    char* inventory_string = (char*)malloc(estimated_length);
    inventory_as_string(inventory, inventory_string, estimated_length);
    
    if (strncmp(inventory_string, expected_string, strlen(expected_string)) != 0){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected \n%s \ngot \n%s\n", testname, expected_string, inventory_string); 
    }
    
    if (highest_volume->pence_spent != 1230){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=%d is not £12.80.\n", testname, highest_volume->pence_spent);
    }
    if (highest_volume->volume != 19){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=%d is not 19.\n", testname, highest_volume->volume);
    }
    
    if(highest_volume->date.dayOfMonth != 24 || highest_volume->date.month != 2 || highest_volume->date.year != 1980 ){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=%0.2d/%0.2d/%0.4d is not 24/02/1980.\n", testname, highest_volume->date.dayOfMonth, highest_volume->date.month, highest_volume->date.year);
    }
    
}


int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% SalesSimpleTest\n");
    printf("%%SUITE_STARTED%%\n");
    //SUITE START***********************************************************
    
    clock_t start, end;
    double duration;
    double total_duration = 0.0f;
    char* testname;
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanLoadLedger";
    printf("%%TEST_STARTED%% %s (SalesSimpleTest)\n", testname);
    testCanLoadLedger(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (SalesSimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanPrintSales";
    printf("%%TEST_STARTED%% %s (SalesSimpleTest)\n", testname);
    testCanPrintSales(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (SalesSimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanApplySalesAndReportFailures";
    printf("%%TEST_STARTED%% %s (SalesSimpleTest)\n", testname);
    testCanApplySalesAndReportFailures(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (SalesSimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    
    //Start test***************************************************************************************************
    
    //INIT CLOCK, RUN TEST AND CALCULATE DURATION
    start = clock();
    testname = "testCanApplySalesAndDetermineHighestVolumeDate";
    printf("%%TEST_STARTED%% %s (SalesSimpleTest)\n", testname);
    testCanApplySalesAndDetermineHighestVolumeDate(testname);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%%TEST_FINISHED%% time=%f %s (SalesSimpleTest) \n", duration, testname);
    
    
    //ADD TO TOTAL DURATION OF TEST SUITE
    total_duration = total_duration + duration;
    
    //End test***************************************************************************************************
    
    
    //SUITE FINISH**********************************************************

    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
