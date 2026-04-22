/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_alpha_num
*/

#include "my.h"

int my_alpha_num(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= 'A' && str[i] <= 'Z') &&
            !(str[i] >= 'a' && str[i] <= 'z') &&
            !(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] == '_')) {
            return 0;
        }
    }
    return 1;
}
