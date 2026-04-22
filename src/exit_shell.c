/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_exit
*/

#include "../include/mysh.h"

int display_free_exit(struct_mysh_t *mysh, int value)
{
    mysh->exit_value = value;
    my_putstr("exit\n");
    return free_shell(mysh);
}

int my_exit(struct_mysh_t *mysh)
{
    int value = 0;
    int num = 0;

    if (my_array_size(mysh->tab) == 1) {
        return display_free_exit(mysh, value);
    }
    if (my_array_size(mysh->tab) > 2 ||
    ((mysh->tab[1][0] != '-') && (my_str_isnum(&mysh->tab[1][1]) != 0))) {
        my_putstr_error("exit: Expression Syntax.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    if (mysh->tab[1]) {
        num = my_getnbr(mysh->tab[1]);
        if (num < 0)
            value = (num % 256 + 256) % 256;
        else
            value = num % 256;
    }
    return display_free_exit(mysh, value);
}
