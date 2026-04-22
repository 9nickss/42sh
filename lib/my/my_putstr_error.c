/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_putstr_error
*/

#include <unistd.h>

void my_putstr_error(char const *str)
{
    for (int c = 0; str[c] != '\0'; c++)
        write(2, &str[c], 1);
}
