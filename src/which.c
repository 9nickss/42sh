/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** which
*/

#include "../include/mysh.h"

static int is_builtin(char *cmd)
{
    char *builtins[NB_BUILTIN] = {"exit", "env", "setenv", "unsetenv", "cd",
        "alias", "unalias", "set", "unset", "which"};

    for (int i = 0; i < NB_BUILTIN; i++) {
        if (my_strcmp(cmd, builtins[i]) == 0) {
            printf("%s: shell built-in command.\n", cmd);
            return 1;
        }
    }
    return 0;
}

static int check_alias(char *cmd)
{
    alias_t **head = get_alias();
    alias_t *current = *head;

    while (current != NULL) {
        if (strcmp(current->name, cmd) == 0) {
            printf("%s: \t aliased to %s\n", cmd, current->command);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static char *find_executable(char *cmd, char *path_env)
{
    char *path_copy = strdup(path_env);
    char *path_token = strtok(path_copy, ":");
    char *full_path = NULL;

    while (path_token != NULL) {
        full_path = malloc(strlen(path_token) + strlen(cmd) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }
        sprintf(full_path, "%s/%s", path_token, cmd);
        if (access(full_path, F_OK | X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        path_token = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

void find_if_command(struct_mysh_t *mysh, int i, which_t *stock)
{
    stock->status = 0;
    stock->path_env = get_var_value(mysh, "PATH");
    if (!stock->path_env)
        stock->path_env = strdup("/bin:/usr/bin");
    stock->executable_path = find_executable(mysh->tab[i], stock->path_env);
    if (stock->executable_path) {
        printf("%s\n", stock->executable_path);
        free(stock->executable_path);
        stock->found = 1;
    } else if (access(mysh->tab[i], F_OK | X_OK) == 0) {
        printf("%s\n", mysh->tab[i]);
        stock->found = 1;
    }
    if (!stock->found) {
        printf("%s: Command not found.\n", mysh->tab[i]);
        stock->status = 1;
    }
}

int my_which(struct_mysh_t *mysh)
{
    which_t *stock = malloc(sizeof(which_t));

    stock->found = 0;
    if (!mysh->tab[1]) {
        printf("which: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; mysh->tab[i]; i++) {
        stock->found = 0;
        if (is_builtin(mysh->tab[i])) {
            stock->found = 1;
            continue;
        }
        if (check_alias(mysh->tab[i])) {
            stock->found = 1;
            continue;
        }
        find_if_command(mysh, i, stock);
    }
    return stock->status;
}
