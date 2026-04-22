/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_array_size
*/

#include "my.h"
#include <stddef.h>

int my_array_size(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}
