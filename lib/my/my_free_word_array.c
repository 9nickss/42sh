/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_free_word_array
*/

#include "my.h"
#include <stdlib.h>

void free_word_array(char ***array)
{
    if (!(*array))
        return;
    for (int i = 0; (*array)[i] != NULL; i++)
        free((*array)[i]);
    free(*array);
    *array = NULL;
}
