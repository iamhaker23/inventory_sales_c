/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedList.h
 * Author: Hakeem
 *
 * Created on 03 November 2017, 13:08
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct _Node{
    int value;
    struct _Node* next;
    struct _Node* previous;
} Node;

typedef struct _List{
    Node* first;
    int length;
    Node* last;
} List;

List* list_new();

void list_fprint(List* list, FILE* fd);

void list_as_string(List* list, char *tmp, int tmp_length);

int list_length(List* list);

void list_tail_insert(List* list, int value);

void list_head_insert(List* list, int value);

int list_pop_head(List* list);

int list_pop_tail(List* list);

void list_empty(List* list);

void list_sort(List* list, int ascendingFlag);

void list_gc(List* list);

int list_memory_size(List* list);

#ifdef __cplusplus
}
#endif

#endif /* LINKEDLIST_H */

