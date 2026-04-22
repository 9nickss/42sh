/*
** EPITECH PROJECT, 2024
** B-MUL-100-NCE-1-1-myhunter-jules.martins
** File description:
** my_int_to_str
*/

#include "my.h"
#include <stdlib.h>

char *my_int_to_str(int points)
{
    char *str;
    int temp = points;
    int length = 0;

    if (points == 0) {
        str = my_strdup("0");
        return str;
    }
    for (; temp > 0; temp /= 10)
        length++;
    str = malloc(length + 1);
    if (!str)
        return NULL;
    str[length] = '\0';
    for (int i = length - 1; points > 0; i--) {
        str[i] = '0' + (points % 10);
        points /= 10;
    }
    return str;
}
