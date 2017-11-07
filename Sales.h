/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sales.h
 * Author: Hakeem
 *
 * Created on 03 November 2017, 12:07
 */

#ifndef SALES_H
#define SALES_H

#include "Date.h"
#include "StockItem.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _Sales{
        Date date;
        StockItem item;
        int quantity;
    }Sales;


#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

