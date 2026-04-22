/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** init_struct
*/

#include "../include/mysh.h"
#include <pwd.h>

linked_list_t *defaults_value(linked_list_t **list)
{
    linked_list_t *new_list = *list;

    add_to_list_back(&new_list,
        "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
    add_to_list_back(&new_list, my_strdup("TERM=xterm"));
    add_to_list_back(&new_list, my_strdup("NLSPATH=/usr/share/locale/%L/%N"));
    return new_list;
}

struct_mysh_t *init_struct(char **env)
{
    struct_mysh_t *mysh = malloc(sizeof(struct_mysh_t));
    linked_list_t *list = NULL;

    if (!mysh)
        return NULL;
    if (env && env[0] != NULL) {
        list = env_to_ll(env);
    } else {
        list = NULL;
        list = defaults_value(&list);
    }
    mysh->list = list;
    mysh->local_vars = NULL;
    mysh->exit_value = 0;
    mysh->old_pwd = NULL;
    mysh->history = NULL;
    return mysh;
}
