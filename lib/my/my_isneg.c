/*
** EPITECH PROJECT, 2024
** Isneg
** File description:
** That display if numbers are negatives or positives
*/

#include <unistd.h>

int my_isneg(int n)
{
    if (n < 0) {
        write(1, "N", 1);
    } else {
        write(1, "P", 1);
    }
    return 0;
}
