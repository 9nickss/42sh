/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** backticks
*/

#include "../include/mysh.h"
#include <string.h>

static int child(int pipefd[2], char *cmd, struct_mysh_t *sh, pid_t pid)
{
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        parse_command(sh, (char *)cmd);
        exit(0);
    }
    return 1;
}

static int create_fork(pid_t *pid, char *result)
{
    *pid = fork();
    if (*pid == -1) {
        perror("fork");
        free(result);
        return 0;
    }
    return 1;
}

static int init_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

static char *read_from_buffer(int pipefd[0])
{
    char buffer[1024];
    ssize_t bytes_read;
    char *result = NULL;

    bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        result = malloc(bytes_read + 1);
        if (result)
            strcpy(result, buffer);
    }
    return result;
}

char *execute_command(char *cmd, struct_mysh_t *sh)
{
    int pipefd[2];
    pid_t pid;
    char *result = NULL;

    if (init_pipe(pipefd) == -1)
        return NULL;
    if (!create_fork(&pid, NULL))
        return NULL;
    child(pipefd, cmd, sh, pid);
    close(pipefd[1]);
    result = read_from_buffer(pipefd);
    close(pipefd[0]);
    wait(NULL);
    return result;
}

char *fill_last_cmd(struct_mysh_t *sh, char *input, char *end, char *start)
{
    char *cmd = strndup(start + 1, end - start - 1);
    char *output = execute_command(cmd, sh);
    char *new_cmd = NULL;
    size_t new_len = 0;

    free(cmd);
    if (!output) {
        fprintf(stderr, "Erreur : execution of backticks command\n");
        return NULL;
    }
    new_len = strlen(input) - (end - start + 1) + strlen(output);
    new_cmd = malloc(new_len + 1);
    if (!new_cmd) {
        free(output);
        return NULL;
    }
    snprintf(new_cmd, new_len + 1, "%.*s%s%s",
        (int)(start - input), input, output, end + 1);
    free(output);
    return new_cmd;
}

char *substitute_backticks(const char *input, struct_mysh_t *sh)
{
    char *start = strchr(input, '`');
    char *end = NULL;
    char *result = NULL;

    if (!start)
        return strdup(input);
    end = strchr(start + 1, '`');
    if (!end) {
        fprintf(stderr, "Erreur : backtick non fermé\n");
        return NULL;
    }
    result = fill_last_cmd(sh, (char *)input, end, start);
    if (!result)
        return NULL;
    return result;
}
