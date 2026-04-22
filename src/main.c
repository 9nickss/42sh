/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include "../include/mysh.h"

int parse_ptr(char *str)
{
    char *type[NB_BUILTIN] = {"exit", "env", "setenv", "unsetenv", "cd",
        "alias", "unalias", "set", "unset", "history"};

    for (int i = 0; i < NB_BUILTIN; i++) {
        if (my_strcmp(str, type[i]) == 0)
            return i;
    }
    return -1;
}

static int is_existing_command(struct_mysh_t *mysh)
{
    char *path = find_path(mysh);

    if (mysh->tab[0][0] == '/' || mysh->tab[0][0] == '.')
        if (access(mysh->tab[0], F_OK | X_OK) == 0)
            path = my_strdup(mysh->tab[0]);
    if (!path) {
        my_putstr_error(mysh->tab[0]);
        my_putstr_error(": Command not found.\n");
        return 1;
    }
    free(path);
    return 0;
}

int check_builtin(struct_mysh_t *mysh, char *line)
{
    alias_t **head = get_alias();

    mysh->tab = inhibitor_parsing(line, " \"\t\\");
    if (!mysh->tab)
        return 0;
    if (resolve_and_update_alias(mysh, head, line))
        return 1;
    expand_command_vars(mysh);
    if (process_wildcards_command(mysh->tab, mysh))
        return fork_without_pipe(mysh);
    if (parse_ptr(mysh->tab[0]) != -1)
        return main_program(mysh);
    if (is_existing_command(mysh) == 1)
        return 1;
    return fork_without_pipe(mysh);
}

int main_program(struct_mysh_t *mysh)
{
    int (*builtin[NB_BUILTIN])(struct_mysh_t *) = {my_exit, my_env,
    my_setenv, my_unsetenv, my_cd, my_alias, my_unalias, my_set, my_unset,
    my_history};
    int index = parse_ptr(mysh->tab[0]);

    if (index != -1)
        return builtin[index](mysh);
    if (is_existing_command(mysh) == 1)
        return 1;
    exec_command(mysh);
    return 1;
}

int main(int ac, char **av, char **env)
{
    struct_mysh_t *mysh = init_struct(env);

    av = av;
    ac = ac;
    while (1)
        mysh->exit_value = mainloop(mysh);
    return free_shell(mysh);
}
