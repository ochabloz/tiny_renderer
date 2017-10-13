#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdint.h"

typedef struct linked_list * linked_list_t;

linked_list_t linked_list_create(void);
void linked_list_delete(linked_list_t list);
void * linked_list_get(linked_list_t list, uint32_t item_num);
int linked_list_size(linked_list_t list);
void linked_list_add(linked_list_t list, void* item);
#endif
