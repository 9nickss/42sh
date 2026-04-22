/*
** EPITECH PROJECT, 2024
** String string
** File description:
** Reproduce the strstr function
*/

#include <string.h>
#include <stdio.h>

int result(char *str, char const *to_find, int ct_str)
{
    int ct_find = 0;

    while (to_find[ct_find] != '\0' && str[ct_str + ct_find] != '\0' &&
        to_find[ct_find] == str[ct_str + ct_find]) {
        ct_find++;
    }
    if (to_find[ct_find] == '\0')
        return 1;
    return 0;
}

char *my_strstr(char *str, char const *to_find)
{
    int ct_str = 0;
    int a = 0;

    if (to_find[0] == '\0')
        return str;
    for (ct_str = 0; str[ct_str] != '\0'; ct_str++) {
        a = result(str, to_find, ct_str);
        if (a == 1)
            return &str[ct_str];
    }
    return NULL;
}
