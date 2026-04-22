/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** semicolon
*/

#include "../include/mysh.h"

int clear_token(char **token, char **saveptr)
{
    char *end = NULL;

    while (*(*token) == ' ' || *(*token) == '\t' || *(*token) == '\n')
        (*token)++;
    if (*(*token) == '\0') {
        (*token) = strtok_r(NULL, ";", saveptr);
        return 84;
    }
    end = *token + strlen(*token) - 1;
    while (end > *token && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = '\0';
        end--;
    }
    return 0;
}

int parse_command(struct_mysh_t *mysh, char *line)
{
    char *saveptr = NULL;
    char *token = strtok_r(line, ";", &saveptr);
    int exit_value = 0;

    while (token) {
        if (clear_token(&token, &saveptr) == 84)
            continue;
        if (strstr(line, "&&") || strstr(line, "||"))
            return execute_and_or(mysh, line);
        exit_value = check_builtin(mysh, token);
        if (my_strchr(token, '|') != NULL)
            return exec_pipe(mysh, token);
        free_word_array(&mysh->tab);
        token = strtok_r(NULL, ";", &saveptr);
    }
    return exit_value;
}
