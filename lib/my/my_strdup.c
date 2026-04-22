/*
** EPITECH PROJECT, 2024
** My string duplicate
** File description:
** Copy a string and allocate memory
*/
#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int lensrc = my_strlen(src);
    char *dup;

    if (!src)
        return NULL;
    dup = malloc(sizeof(char) * (lensrc + 1));
    if (!dup)
        return NULL;
    for (int ct_src = 0; src[ct_src] != '\0'; ct_src++)
        dup[ct_src] = src[ct_src];
    dup[lensrc] = '\0';
    return dup;
}
