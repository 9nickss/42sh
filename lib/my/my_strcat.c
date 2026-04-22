/*
** EPITECH PROJECT, 2024
** String cat
** File description:
** Concatenates two strings in param
*/
#include <string.h>

char *my_strcat(char *dest, char const *src)
{
    int count_src = 0;
    int len_dest = 0;

    while (dest[len_dest]) {
        len_dest++;
    }
    while (src[count_src]) {
        dest[len_dest + count_src] = src[count_src];
        count_src++;
    }
    dest[len_dest + count_src] = '\0';
    return dest;
}
