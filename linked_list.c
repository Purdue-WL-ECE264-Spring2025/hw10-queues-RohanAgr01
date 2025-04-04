#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node) return NULL;
    node->value = value;
    node->next = node->prev = NULL;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (!node) return;

    node->next = list->head;
    if (list->head) list->head->prev = node;
    list->head = node;
    if (!list->tail) list->tail = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (!node) return;

    node->prev = list->tail;
    if (list->tail) list->tail->next = node;
    list->tail = node;
    if (!list->head) list->head = node;
}

size_t remove_from_head(struct linked_list *list) {
    if (!list->head) return 0;

    struct list_node *node = list->head;
    size_t value = node->value;
    
    list->head = node->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;

    free(node);
    return value;
}

size_t remove_from_tail(struct linked_list *list) {
    if (!list->tail) return 0;

    struct list_node *node = list->tail;
    size_t value = node->value;

    list->tail = node->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;

    free(node);
    return value;
}

void free_list(struct linked_list list) {
    struct list_node *current = list.head;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}
