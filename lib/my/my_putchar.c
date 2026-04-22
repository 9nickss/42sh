/*
** EPITECH PROJECT, 2024
** Putchar
** File description:
** Print character
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
