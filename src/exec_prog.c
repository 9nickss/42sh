/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** exec_prog
*/

#include "../include/mysh.h"

int error_execve(struct_mysh_t *mysh, char **env)
{
    mysh->exit_value = 1;
    my_putstr_error(mysh->tab[0]);
    if (errno == EACCES)
        my_putstr_error(": Permission denied.\n");
    if (errno == ENOENT)
        my_putstr_error(": Command not found.\n");
    if (errno == ENOEXEC)
        my_putstr_error(": Exec format error. Binary file not executable.\n");
    if (errno != (ENOEXEC && ENOENT && EACCES)) {
        my_putstr_error(": ");
        my_putstr_error(strerror(errno));
        my_putstr_error(".\n");
        mysh->exit_value = errno;
    }
    free_word_array(&env);
    free_word_array(&mysh->tab);
    return free_shell(mysh);
}

int handle_signal(struct_mysh_t *mysh, int status)
{
    int sig = 0;
    int core_dumped = 0;

    if (!WIFSIGNALED(status))
        return mysh->exit_value;
    sig = WTERMSIG(status);
    core_dumped = WCOREDUMP(status);
    if (sig == SIGFPE)
        my_putstr_error("Floating exception");
    else if (sig == SIGSEGV)
        my_putstr_error("Segmentation fault");
    if (core_dumped)
        my_putstr_error(" (core dumped)");
    my_putstr_error("\n");
    mysh->exit_value = 128 + sig;
    return mysh->exit_value;
}

int exec_command(struct_mysh_t *mysh)
{
    char *path = find_path(mysh);
    char **env = ll_to_env(mysh->list);

    if (mysh->tab[0][0] == '/' || mysh->tab[0][0] == '.')
        if (access(mysh->tab[0], F_OK | X_OK) == 0)
            path = my_strdup(mysh->tab[0]);
    if (execve(path, mysh->tab, env) == -1)
        return error_execve(mysh, env);
    return mysh->exit_value;
}

int fork_without_pipe(struct_mysh_t *mysh)
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
        exit(main_program(mysh));
    else if (pid > 0) {
        waitpid(pid, &status, 0);
        mysh->exit_value = WEXITSTATUS(status);
        return handle_signal(mysh, status);
    } else {
        perror("fork");
        return 84;
    }
    return mysh->exit_value;
}
