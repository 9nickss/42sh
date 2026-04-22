/*
** EPITECH PROJECT, 2024
** Putstr
** File description:
** Displays one by one the characters of a string
*/

#include <unistd.h>

void my_putstr(char const *str)
{
    for (int c = 0; str[c] != '\0'; c++)
        write(1, &str[c], 1);
}
