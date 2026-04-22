/*
** EPITECH PROJECT, 2024
** String lowcase
** File description:
** Put every char in low
*/
#include <string.h>
#include <stdio.h>

char *my_strlowcase(char *str)
{
    int ct_str = 0;

    while (str[ct_str]) {
        if (str[ct_str] <= 'Z' && 'A' <= str[ct_str]) {
            str[ct_str] = str[ct_str] + 32;
        }
        ct_str++;
    }
    return str;
}
