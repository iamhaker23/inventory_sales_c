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
    
    char* exp_code;
    int exp_quantity;
    
    exp_code = "CAP_150pF";
    exp_quantity = 580;
    
    StockItem* item = get_item_by_product_code(inventory, exp_code);
    
    if (item->quantity != exp_quantity){
        printf("%%TEST_FAILED%% time=0 testname=%s (SalesSimpleTest) message=Expected %s to have \n%d \nbut got \n%d\n", testname, exp_code, exp_quantity, item->quantity ); 
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
    //SUITE FINISH**********************************************************

    printf("%%SUITE_FINISHED%% time=%f\n", total_duration);

    return (EXIT_SUCCESS);
}
