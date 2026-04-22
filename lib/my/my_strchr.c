/*
** EPITECH PROJECT, 2025
** test
** File description:
** my_strchr
*/

#include <stdio.h>

char *my_strchr(const char *str, int c)
{
    while (*str) {
        if (*str == c)
            return (char *)&(*str);
        str++;
    }
    return NULL;
}
