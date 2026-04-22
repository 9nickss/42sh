/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** and_or
*/

#include "../include/mysh.h"

char *fill_first_comand(char *line)
{
    int i = 0;
    int len = 0;
    char *first_command = NULL;
    int start = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    start = i;
    while (line[i] &&
        !(line[i] == '&' && line[i + 1] == '&') &&
        !(line[i] == '|' && line[i + 1] == '|'))
        i++;
    len = i - start;
    first_command = malloc(len + 1);
    if (!first_command)
        return NULL;
    for (int j = 0; j < len; j++)
        first_command[j] = line[start + j];
    first_command[len] = '\0';
    return first_command;
}

static int is_and_or(char *s)
{
    return (s[0] == '&' && s[1] == '&') || (s[0] == '|' && s[1] == '|');
}

static void handle_sep(char **cur, int *i, char **cmds, int *c)
{
    *cur += *i + 2;
    *i = 0;
    cmds[(*c)] = fill_first_comand(*cur);
    (*c)++;
}

char **split_and_or(char *line, int nb)
{
    char **command = malloc(sizeof(char *) * (nb + 2));
    int i = 0;
    int cmd = 0;
    char *current = line;

    if (!command)
        return NULL;
    command[cmd] = fill_first_comand(current);
    cmd++;
    while (current[i]) {
        if (is_and_or(current + i))
            handle_sep(&current, &i, command, &cmd);
        else
            i++;
    }
    command[cmd] = NULL;
    return command;
}

static int count_operators(char *line)
{
    int count = 0;

    for (int i = 0; line[i]; i++) {
        if ((line[i] == '&' && line[i + 1] == '&') ||
            (line[i] == '|' && line[i + 1] == '|')) {
            count++;
            i++;
        }
    }
    return count;
}

static int fill_instr(char *line, int *instr)
{
    int c = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '&' && line[i + 1] == '&') {
            instr[c] = 2;
            c++;
            i++;
        }
        if (line[i] == '|' && line[i + 1] == '|') {
            instr[c] = 1;
            c++;
            i++;
        }
    }
    return c;
}

int exec(struct_mysh_t *mysh,
    char **command, int *instr)
{
    int status = check_builtin(mysh, command[0]);
    int cmd_count = my_array_size(command);

    for (int i = 0; i < cmd_count - 1; i++) {
        if ((instr[i] == 2 && status == 0) ||
            (instr[i] == 1 && status != 0)) {
            status = check_builtin(mysh, command[i + 1]);
        }
    }
    return status;
}

static int null_cmd(char ***command, int nb, int *instr)
{
    if (my_array_size(*command) != nb + 1) {
        fprintf(stderr, "Invalid null command.\n");
        free_word_array(command);
        free(instr);
        return 84;
    }
    return 0;
}

int execute_and_or(struct_mysh_t *mysh, char *line)
{
    int nb = count_operators(line);
    int *instr = malloc(sizeof(int) * nb);
    char **command = NULL;
    int status = 0;

    if (!instr)
        return 1;
    fill_instr(line, instr);
    command = split_and_or(line, nb);
    if (!command) {
        free(instr);
        return 1;
    }
    if (null_cmd(&command, nb, instr) == 84)
        return 84;
    status = exec(mysh, command, instr);
    free_word_array(&command);
    free(instr);
    return status;
}
