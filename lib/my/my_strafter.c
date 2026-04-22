/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strafter
*/

#include <string.h>
#include <stdio.h>

static int result(char *str, char const *to_find, int ct_str)
{
    int ct_find = 0;

    while (to_find[ct_find] != '\0' && str[ct_str + ct_find] != '\0' &&
        to_find[ct_find] == str[ct_str + ct_find]) {
        ct_find++;
    }
    if (to_find[ct_find] == '\0')
        return ct_find;
    return 0;
}

char *my_strafter(char *str, char const *to_find)
{
    int ct_str = 0;
    int res = 0;

    if (to_find[0] == '\0')
        return str;
    for (ct_str = 0; str[ct_str] != '\0'; ct_str++) {
        res = result(str, to_find, ct_str);
        if (res != 0)
            return &str[ct_str + res];
    }
    return NULL;
}
