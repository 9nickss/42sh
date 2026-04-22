/*
** EPITECH PROJECT, 2024
** Swap
** File description:
** Swap the content of two integers
*/

void my_swap(int *a, int *b)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
}
