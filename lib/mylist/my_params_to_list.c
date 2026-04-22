/*
** EPITECH PROJECT, 2025
** solostumper02
** File description:
** my_params_to_list
*/

#include "mylist.h"

int add_to_list(linked_list_t **list, char *str)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));

    if (!new)
        return 84;
    new->data = (void *)str;
    new->next = *list;
    *list = new;
    return 0;
}

linked_list_t *my_params_to_list(int ac, char *const *av)
{
    linked_list_t *list = NULL;
    int error = 0;

    for (int i = 0; i < ac; i++) {
        error = add_to_list(&list, av[i]);
        if (error == 84)
            return NULL;
    }
    return list;
}
