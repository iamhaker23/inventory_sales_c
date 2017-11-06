/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   date.h
 * Author: Hakeem
 *
 * Created on 05 November 2017, 14:03
 */

#ifndef DATE_H
#define DATE_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _Date{
        int dayOfMonth;
        int month;
        int year;
    } Date;

#ifdef __cplusplus
}
#endif

#endif /* DATE_H */

