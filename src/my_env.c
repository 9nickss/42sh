/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_env
*/

#include "../include/mysh.h"

int print_env(struct_mysh_t *mysh)
{
    linked_list_t *temp = mysh->list;

    while (temp != NULL) {
        my_putstr(temp->data);
        my_putchar('\n');
        temp = temp->next;
    }
    return mysh->exit_value;
}

int my_env(struct_mysh_t *mysh)
{
    if (my_array_size(mysh->tab) != 1) {
        my_putstr_error("env: '");
        my_putstr_error(mysh->tab[1]);
        my_putstr_error("': No such file or directory\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    return print_env(mysh);
}
