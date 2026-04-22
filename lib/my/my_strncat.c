/*
** EPITECH PROJECT, 2024
** String cat n
** File description:
** Concatenates strings with n length in param
*/
#include <string.h>

char *my_strncat(char *dest, char const *src, int n)
{
    int ct_src = 0;
    int len_dest = 0;

    while (dest[len_dest]) {
        len_dest++;
    }
    while (src[ct_src] != '\0' && ct_src < n) {
        dest[len_dest + ct_src] = src[ct_src];
        ct_src++;
    }
    dest[len_dest + ct_src] = '\0';
    return dest;
}
