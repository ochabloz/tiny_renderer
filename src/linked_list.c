
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


#ifndef NULL
#define NULL (void*)0
#endif

struct item_list{
    void* item;
    struct item_list *next;
};

typedef struct item_list item_list;

struct linked_list{
    int nb_elem;
    item_list* first_item;
};

item_list ** get_last_item(linked_list_t list){
    item_list ** head = &(list->first_item);
    while (*head != NULL){
        item_list * tmp = *head;
        head = &(tmp->next);
    }
    return head;
}

linked_list_t linked_list_create(void){
    linked_list_t list = malloc(sizeof(struct linked_list));
    list->nb_elem = 0;
    list->first_item = NULL;
    return list;
}

void linked_list_delete(linked_list_t list){
    item_list * next = list->first_item;
    while(next != NULL){
        item_list * to_del = next;
        next = next->next;
        free(to_del);
    }
    free(list);
}


int linked_list_size(linked_list_t list){
    return list->nb_elem;
}

void linked_list_add(linked_list_t list, void* item){
    item_list * new_item = malloc(sizeof(item_list));
    new_item->item = item;
    new_item->next = NULL;
    item_list ** attach_to = get_last_item(list);
    if(attach_to != NULL){
        *attach_to = new_item;
        list->nb_elem++;
    }
}


void * linked_list_get(linked_list_t list, uint32_t item_num){
    if(list->nb_elem == 0 || list->nb_elem <= item_num){
        return NULL;
    }
    item_list * current_item = list->first_item;
    for(int i = 0; i < item_num; i++){
        current_item = current_item->next;
    }
    return current_item->item;
}
