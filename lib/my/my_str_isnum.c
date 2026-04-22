/*
** EPITECH PROJECT, 2024
** oiezrher
** File description:
** ruvherui
*/

#include <stdio.h>

int my_str_isnum(char const *str)
{
    if (str == NULL || *str == '\0')
        return 84;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 84;
    }
    return 0;
}
