/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** free_linked_list
*/

#include "mylist.h"

void free_linked_list(linked_list_t *list)
{
    linked_list_t *temp;
    linked_list_t *next;

    while (list != NULL) {
        temp = list;
        next = list->next;
        free(temp);
        list = next;
    }
}
