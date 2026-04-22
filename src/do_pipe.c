/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** do_pipe
*/

#include "../include/mysh.h"

static int exec_child_process(struct_mysh_t *mysh, char *token,
    pipe_data_t *pipes)
{
    int exit_value = 0;

    if (!pipes->is_first_cmd) {
        dup2(pipes->prev_pipe[0], STDIN_FILENO);
        close(pipes->prev_pipe[0]);
    }
    if (pipes->has_next) {
        dup2(pipes->curr_pipe[1], STDOUT_FILENO);
        close(pipes->curr_pipe[0]);
        close(pipes->curr_pipe[1]);
    }
    mysh->tab = inhibitor_parsing(token, " \"\t\\");
    if (mysh->tab) {
        exit_value = main_program(mysh);
        free_word_array(&mysh->tab);
    }
    return exit_value;
}

static void handle_parent_pipes(pipe_data_t *pipes)
{
    if (!pipes->is_first_cmd)
        close(pipes->prev_pipe[0]);
    if (pipes->has_next) {
        close(pipes->curr_pipe[1]);
        pipes->prev_pipe[0] = pipes->curr_pipe[0];
    }
}

static int prepare_pipe(pipe_data_t *pipes)
{
    if (pipes->has_next) {
        if (pipe(pipes->curr_pipe) == -1) {
            perror("pipe");
            return -1;
        }
    } else
        pipes->curr_pipe[1] = STDOUT_FILENO;
    return 0;
}

static void init_pipe_data(pipe_data_t *pipes, int is_first,
    char *next_token)
{
    pipes->is_first_cmd = is_first;
    pipes->has_next = (next_token != NULL);
    if (is_first) {
        pipes->prev_pipe[0] = STDIN_FILENO;
        pipes->prev_pipe[1] = STDOUT_FILENO;
    }
}

static int process_command(struct_mysh_t *mysh, char *token,
    pipe_data_t *pipes)
{
    int exit_value = 0;
    int status;
    pid_t pid;

    if (prepare_pipe(pipes) == -1)
        return -1;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0)
        exit(exec_child_process(mysh, token, pipes));
    handle_parent_pipes(pipes);
    if (!pipes->has_next) {
        waitpid(pid, &status, 0);
        exit_value = WEXITSTATUS(status);
    }
    return exit_value;
}

int exec_pipe(struct_mysh_t *mysh, char *line)
{
    char *saveptr = NULL;
    char *token = strtok_r(line, "|", &saveptr);
    pipe_data_t pipes;
    int exit_value = 0;
    int is_first_cmd = 1;
    char *next_token;

    while (token) {
        next_token = strtok_r(NULL, "|", &saveptr);
        init_pipe_data(&pipes, is_first_cmd, next_token);
        exit_value = process_command(mysh, token, &pipes);
        is_first_cmd = 0;
        token = next_token;
    }
    while (waitpid(-1, NULL, 0) > 0);
    return exit_value;
}
