/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** parse_env
*/

#include "../include/mysh.h"

char **parse_env(struct_mysh_t *mysh, char *id, int size)
{
    linked_list_t *temp = mysh->list;

    for (; temp != NULL; temp = temp->next) {
        if (my_strncmp((const char *)temp->data, id, size) == 0)
            return my_str_to_word_array((const char *)temp->data, "=:");
    }
    return NULL;
}

char *find_path(struct_mysh_t *mysh)
{
    char **str = parse_env(mysh, "PATH", 4);
    char *path = NULL;

    if (access(mysh->tab[0], F_OK | X_OK) == 0)
        return my_strdup(mysh->tab[0]);
    for (int i = 0; str[i] != NULL; i++) {
        path = malloc(my_strlen(str[i]) + my_strlen(mysh->tab[0]) + 2);
        if (!path)
            return NULL;
        my_strcpy(path, str[i]);
        my_strcat(path, "/");
        my_strcat(path, mysh->tab[0]);
        if (access(path, F_OK | R_OK) == 0) {
            free_word_array(&str);
            return path;
        }
        free(path);
    }
    free_word_array(&str);
    return NULL;
}
