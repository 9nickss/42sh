/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** unsetenv
*/

#include "../include/mysh.h"

int my_unsetenv(struct_mysh_t *mysh)
{
    char **str = NULL;

    if (my_array_size(mysh->tab) == 1) {
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    for (int i = 1; mysh->tab[i] != NULL; i++) {
        str = parse_env(mysh, mysh->tab[i], my_strlen(mysh->tab[i]));
        if (str != NULL)
            remove_node(&mysh->list, mysh->tab[i], my_strlen(mysh->tab[i]));
        free_word_array(&str);
    }
    return mysh->exit_value;
}
