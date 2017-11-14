/* 
 * File:   StockProgram.c
 * Author: Hakeem
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Inventory.h"
#include "Sales.h"


/*
 * Entry point for StockProgram.
 * 
 * Input: inventory.txt, sales.txt
 * Output: StockProgram.log, stdout/stderr
 * 
 */
int main(int argc, char** argv) {

    //Initialise inventory and sales lists
    Inventory* inventory = inventory_new();
    Sales* sales_ledger = sales_ledger_new();
    
    //Open log or exit
    FILE* log = fopen("StockProgram.log", "w");
    if (log == NULL){
        fprintf(stderr, "Couldn't create log file \"StockProgram.log\"\r\n");
        exit(EXIT_FAILURE);
    }
    
    //Starting program
    fprintf(log, "Starting StockProgram.\r\n");
    printf("Starting StockProgram.\r\n");
    
    //open input files or exit
    FILE* inventory_file = fopen("inventory.txt", "r");
    FILE* sales_file = fopen("sales.txt", "r");
    
    if (inventory_file == NULL || sales_file == NULL){
        fprintf(log, "%s%ld\r\n", "Inventory file@", (long)inventory_file);
        fprintf(log, "%s%ld\r\n", "Sales file@", (long)sales_file);
        fflush(log);
    
        fprintf(stderr, "%s, see StockProgram.log for details.\r\n", "Couldn't find data");
        exit(EXIT_FAILURE);
    }
    
    //load file data into lists
    load_inventory(inventory_file, inventory);
    load_sales_ledger(sales_file, sales_ledger, inventory);
    
    //done with file data, close file streams
    fclose(inventory_file);
    fclose(sales_file);
    free(inventory_file);
    free(sales_file);
    
    //Debug - count loaded data records
    int inventory_l = inventory_length(inventory);
    int sales_l = sales_ledger_length(sales_ledger);
    fprintf(log,"Inventory loaded %d items.\r\n", inventory_l);
    fprintf(log,"Sales Ledger loaded %d sales.\r\n", sales_l);
    fflush(log);
    
    //Debug - show metrics generated before sales
    printf("METRICS BEFORE SALES***************\r\n\r\n");
    fprintf(log, "METRICS BEFORE SALES***************\r\n\r\n");
    fflush(log);
    
    //count NPN transistors
    int total_npn_resistors = count_type_matching_description_in_stock(inventory, "transistor", "NPN");
    printf("Total NPN transistors (in stock): %d\r\n", total_npn_resistors);
    fprintf(log, "Total NPN transistors (in stock): %d\r\n", total_npn_resistors);
    fflush(log);
    
    //aggregate resistance values
    float total_resistance = total_resistance_of_in_stock_resistors(inventory);
    printf("Total resistance of all resistors (in stock): %.2f\r\n", total_resistance);
    fprintf(log, "Total resistance of all resistors (in stock): %.2f\r\n", total_resistance);
    fflush(log);
    
    //apply sales ledger to inventory, record highest volume stats
    Sales_Volume* highest_volume = apply_sales_to_inventory(sales_ledger, inventory, log);
    
    //After sales output - Q1 (print inventory in price ascending order)
    int estimated_required_length = inventory_estimate_required_buffer(inventory);
    fprintf(log, "Inventory string length:%d.\r\n", estimated_required_length);
    fflush(log);
    
    char* inventory_str = (char*)malloc(estimated_required_length);
    
    inventory_sort(inventory, 1);
    fprintf(log, "Inventory sorted successfully.\r\n");
    fflush(log);
    
    inventory_as_csv(inventory, inventory_str, estimated_required_length);
    fprintf(log, "Inventory (price ascending):\r\n\r\n%s\r\n\r\n", inventory_str);
    fflush(log);
    
    printf("Inventory (price ascending):\r\n\r\n%s\r\n\r\n", inventory_str);
    free(inventory_str);
    
    //After sales output - Q2 (print highest volume stats)
    printf("Highest Sales Volume:\r\nDate:%.2d/%.2d/%.4d\r\nSales:%d\r\nProfit:£%.2f\r\n\r\n", highest_volume->date->dayOfMonth, highest_volume->date->month, highest_volume->date->year, highest_volume->volume, ((float)(highest_volume->pence_spent)/100.0f));
    fprintf(log, "Highest Sales Volume:\r\nDate:%.2d/%.2d/%.4d\r\nSales:%d\r\nProfit:£%.2f\r\n\r\n", highest_volume->date->dayOfMonth, highest_volume->date->month, highest_volume->date->year, highest_volume->volume, ((float)(highest_volume->pence_spent)/100.0f));
    fflush(log);
    
    //After sales output - Q3, Q4 (print NPN transistors in stock, aggregated resistance values")
    printf("METRICS AFTER SALES***************\r\n\r\n");
    fprintf(log, "METRICS AFTER SALES***************\r\n\r\n");
    fflush(log);
    
    //NPN transistor count
    total_npn_resistors = count_type_matching_description_in_stock(inventory, "transistor", "NPN");
    printf("Total NPN transistors (in stock): %d\r\n", total_npn_resistors);
    fprintf(log, "Total NPN transistors (in stock): %d\r\n", total_npn_resistors);
    fflush(log);
    
    //Total resistance
    total_resistance = total_resistance_of_in_stock_resistors(inventory);
    printf("Total resistance of all resistors (in stock): %.2f Ohms\r\n", total_resistance);
    fprintf(log, "Total resistance of all resistors (in stock): %.2f Ohms\r\n", total_resistance);
    fflush(log);
    
    //Debug - garbage collection
    int sizeOfInventory = (sizeof(inventory)) + (inventory_length(inventory)*sizeof(INode));
    printf("Garbage collect inventory list, freeing %d bytes.\r\n", sizeOfInventory);
    fprintf(log, "Garbage collect inventory list, freeing %d bytes.\r\n", sizeOfInventory);
    fflush(log);
    inventory_gc(inventory);
    
    int sizeOfSalesLedger = (sizeof(sales_ledger)) + (sales_ledger_length(sales_ledger)*sizeof(SNode));
    printf("Garbage collect sales list, freeing %d bytes.\r\n", sizeOfSalesLedger);
    fprintf(log, "Garbage collect sales list, freeing %d bytes.\r\n", sizeOfSalesLedger);
    fflush(log);
    sales_ledger_gc(sales_ledger);
    
    //close log file stream and exit
    fclose(log);
    free(log);
    return (EXIT_SUCCESS);
}

