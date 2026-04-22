/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globing
*/
#include "../include/mysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

char **expand_wildcards(char *pattern)
{
    glob_t glob_result;
    char **result = NULL;
    size_t i;

    if (glob(pattern, GLOB_TILDE, NULL, &glob_result) != 0) {
        result = malloc(sizeof(char *) * 2);
        if (result) {
            result[0] = strdup(pattern);
            result[1] = NULL;
        }
        return result;
    }
    result = malloc(sizeof(char *) * (glob_result.gl_pathc + 1));
    if (result) {
        for (i = 0; i < glob_result.gl_pathc; i++)
            result[i] = strdup(glob_result.gl_pathv[i]);
        result[i] = NULL;
    }
    globfree(&glob_result);
    return result;
}

int need_expansion(char **args)
{
    for (int i = 0; args[i]; i++) {
        if (strchr(args[i], '*') ||
        strchr(args[i], '?') || strchr(args[i], '['))
            return 1;
    }
    return 0;
}

static int add_in_tab(char **ar, struct_mysh_t *mysh)
{
    int tab_len = my_array_size(mysh->tab);
    int ar_len = my_array_size(ar);
    int k = 0;
    char **new_tab = malloc(sizeof(char *) * (tab_len + ar_len + 1));

    if (!new_tab)
        return -1;
    for (int i = 0; i < tab_len; i++)
        if (!strchr(mysh->tab[i], '*')) {
            new_tab[k] = strdup(mysh->tab[i]);
            k++;
        }
    for (int j = 0; j < ar_len; j++) {
        new_tab[k] = strdup(ar[j]);
        k++;
    }
    new_tab[k] = NULL;
    free(mysh->tab);
    mysh->tab = new_tab;
    return 0;
}

int process_wildcards_command(char **args, struct_mysh_t *mysh)
{
    char **expanded_args = NULL;
    int i = 0;

    if (!need_expansion(args))
        return 0;
    while (args[i]) {
        if (strchr(args[i], '*') ||
        strchr(args[i], '?') || strchr(args[i], '[')) {
            expanded_args = expand_wildcards(args[i]);
        }
        i++;
    }
    add_in_tab(expanded_args, mysh);
    for (int j = 0; expanded_args[j]; j++)
        free(expanded_args[j]);
    free(expanded_args);
    return 1;
}
