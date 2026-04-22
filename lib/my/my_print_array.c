/*
** EPITECH PROJECT, 2024
** lyutnumber
** File description:
** len_array
*/

#include "my.h"
#include <unistd.h>

void my_print_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        my_putstr(array[i]);
        write(1, "\n", 1);
    }
}
