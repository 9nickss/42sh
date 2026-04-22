/*
** EPITECH PROJECT, 2024
** String compare
** File description:
** String compare characters between first & second
*/
#include <stdio.h>
#include <string.h>

int my_strcmp(char const *s1, char const *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
