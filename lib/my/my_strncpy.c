/*
** EPITECH PROJECT, 2024
** Copy string length
** File description:
** Copy a string with the length
*/
#include <stdio.h>

char *my_strncpy(char *dest, char const *src, int n)
{
    int count_char = 0;

    while (count_char < n) {
        if (src[count_char] != '\0') {
            dest[count_char] = src[count_char];
            count_char++;
        }
    }
    while (src[count_char] != '\0') {
        dest[count_char] = '\0';
        count_char++;
    }
    return dest;
}
