/*
** EPITECH PROJECT, 2024
** String upcase
** File description:
** Put every char in maj
*/
#include <string.h>
#include <stdio.h>

char *my_strupcase(char *str)
{
    int ct_str = 0;

    while (str[ct_str]) {
        if (str[ct_str] <= 'z' && 'a' <= str[ct_str]) {
            str[ct_str] = str[ct_str] - 32;
        }
        ct_str++;
    }
    return str;
}
