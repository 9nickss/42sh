/*
** EPITECH PROJECT, 2024
** my_getnbr.c
** File description:
** get number
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int number = 0;
    int sign = 1;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    if ('0' > str[i] || str[i] > '9')
        return 0;
    for (int j = 0; (48 <= str[i + j]) && (str[i + j] <= 57); j++)
        number = number * 10 + (str[i + j] - 48);
    if ((number * sign < -2147483647) || number > 2147483647)
        return 0;
    return (number * sign);
}
