/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** setenv
*/

#include "../include/mysh.h"

int error(struct_mysh_t *mysh)
{
    if (!(mysh->tab[1][0] >= 'A' && mysh->tab[1][0] <= 'Z') &&
        !(mysh->tab[1][0] >= 'a' && mysh->tab[1][0] <= 'z') &&
        !(mysh->tab[1][0] == '_')) {
        my_putstr_error(mysh->tab[0]);
        my_putstr_error(": Variable name must begin with a letter.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    if (my_alpha_num(&mysh->tab[1][1]) == 0) {
        my_putstr_error(mysh->tab[0]);
        my_putstr_error(
            ": Variable name must contain alphanumeric characters.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    return mysh->exit_value;
}

void copy_into_ll(struct_mysh_t *mysh)
{
    const char *value = (mysh->tab[2] == NULL) ? "" : mysh->tab[2];
    char *str = malloc(my_strlen(mysh->tab[1]) + my_strlen(value) + 2);

    if (!str)
        return;
    my_strcpy(str, mysh->tab[1]);
    my_strcat(str, "=");
    my_strcat(str, value);
    add_to_list_back(&mysh->list, str);
}

int my_setenv(struct_mysh_t *mysh)
{
    char **str = NULL;

    if (my_array_size(mysh->tab) == 1)
        return print_env(mysh);
    if (my_array_size(mysh->tab) > 3) {
        my_putstr_error("setenv: Too many arguments.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    if (error(mysh) == 1) {
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    str = parse_env(mysh, mysh->tab[1], my_strlen(mysh->tab[1]));
    if (str != NULL)
        remove_node(&mysh->list, mysh->tab[1], my_strlen(mysh->tab[1]));
    free_word_array(&str);
    copy_into_ll(mysh);
    return mysh->exit_value;
}
