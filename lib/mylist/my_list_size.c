/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_list_size
*/

#include "mylist.h"

int my_list_size(linked_list_t const *begin)
{
    int size = 0;
    linked_list_t const *temp = begin;

    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}
