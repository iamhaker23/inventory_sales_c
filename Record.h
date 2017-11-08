/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record.h
 * Author: Hakeem
 *
 * Created on 08 November 2017, 18:10
 */

#include "Date.h"

#ifndef RECORD_H
#define RECORD_H

#ifdef __cplusplus
extern "C" {
#endif


    typedef struct _Record{
        Date date;
        StockItem item;
        int quantity;
    }Record;

#ifdef __cplusplus
}
#endif

#endif /* RECORD_H */

