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
/*
 * Simple C Test Suite
 */

void test2() {
    printf("SalesSimpleTest test 2\n");
    
    Sales* sales = sales_ledger_new();
    
    Inventory* inventory = inventory_new();
    
    FILE* fd = fopen("testdata.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=test2 (SalesSimpleTest) message=error message sample\n");
    }
    
    load_inventory(fd, inventory);
    fclose(fd);
    
    fd = fopen("testdata_sales.txt", "r");
    if (fd == NULL){
        printf("%%TEST_FAILED%% time=0 testname=test2 (SalesSimpleTest) message=error message sample\n");
    }
    
    if (sales_ledger_length(sales) != 0){
        printf("%%TEST_FAILED%% time=0 testname=test2 (SalesSimpleTest) message=error message sample\n");
    }
    
    load_sales_ledger(fd, sales, inventory);
    
    if (sales_ledger_length(sales) != 8){
        printf("%%TEST_FAILED%% time=0 testname=test2 (SalesSimpleTest) message=expected 8 got %d.\n", sales_ledger_length(sales));
    }
    
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% SalesSimpleTest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test2 (SalesSimpleTest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (SalesSimpleTest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
