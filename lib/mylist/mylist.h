/*
** EPITECH PROJECT, 2025
** list h
** File description:
** list h
*/

#ifndef _LIST_H_
    #define _LIST_H_

    #include <stdlib.h>

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

linked_list_t *my_params_to_list(int ac, char *const *av);
int my_list_size(linked_list_t const *begin);
void my_rev_list(linked_list_t **begin);
int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *));
void free_linked_list(linked_list_t *list);

#endif /* _LIST_H_ */
