/*
** EPITECH PROJECT, 2024
** Strlen
** File description:
** Counts and returns the number of characters
*/

#include "stdlib.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    for (; str[i] != '\0'; i++);
    return i;
}
