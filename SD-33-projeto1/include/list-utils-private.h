// This file was developed by June Wilson 61795
#ifndef _LIST_UTILS_PRIAVTE_H
#define _LIST_UTILS_PRIAVTE_H

int contains(char** array, char* item, int size);

struct list_t* split(struct list_t* list);

struct list_t* merge(struct list_t* first, struct list_t* second);

struct list_t* mergesort(struct list_t* list);

int destroy_node(struct car_t* node);

#endif