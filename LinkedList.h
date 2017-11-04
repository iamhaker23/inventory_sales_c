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

typedef Node* Iterator;

static inline Iterator list_begin(const List *list)
{
   return list->first;
}

static inline Iterator list_end(const List *list)
{
   return NULL;
}

static inline Iterator iterator_next(const Iterator i)
{
   return i->next;
}

static inline int iterator_value(const Iterator i)
{
    return i->value;
}

static inline Iterator iterator_set(Iterator i, int value)
{
    i->value = value;
}

List* list_new();

void list_fprint(List* list, FILE* fd);

char* list_as_string(List* list, char *tmp);

int list_length(List* list);

void list_tail_insert(List* list, int value);

void list_head_insert(List* list, int value);

int list_pop_head(List* list);

int list_pop_tail(List* list);

void list_empty(List* list);

void list_sort(List* list, int ascendingFlag);

void list_gc(List* list);

int list_memory_size(List* list);

#endif /* LINKEDLIST_H */

