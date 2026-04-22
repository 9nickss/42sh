/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_cd
*/

#include "../include/mysh.h"

void new_pwd(struct_mysh_t *mysh, char *pwd)
{
    if (mysh->old_pwd)
        free(mysh->old_pwd);
    mysh->old_pwd = pwd ? my_strdup(pwd) : getcwd(NULL, 0);
}

int home_pwd(struct_mysh_t *mysh)
{
    char **home = parse_env(mysh, "HOME", 4);

    if (!home || !home[1]) {
        my_putstr_error("cd: No home directory.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    new_pwd(mysh, NULL);
    if (chdir(home[1]) != 0) {
        my_putstr_error(": ");
        my_putstr_error(strerror(errno));
        my_putstr_error(".\n");
        free_word_array(&home);
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    free_word_array(&home);
    return mysh->exit_value;
}

int old_pwd(struct_mysh_t *mysh)
{
    char *pwd = getcwd(NULL, 0);

    if (!mysh->old_pwd) {
        my_putstr_error(": Not a directory.\n");
        free(pwd);
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    if (chdir(mysh->old_pwd) != 0) {
        my_putstr_error(": ");
        my_putstr_error(strerror(errno));
        my_putstr_error(".\n");
        free(pwd);
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    new_pwd(mysh, pwd);
    free(pwd);
    return mysh->exit_value;
}

int classic_cd(struct_mysh_t *mysh)
{
    char *pwd = getcwd(NULL, 0);

    if (chdir(mysh->tab[1]) != 0) {
        my_putstr_error(mysh->tab[1]);
        my_putstr_error(": ");
        my_putstr_error(strerror(errno));
        my_putstr_error(".\n");
        free(pwd);
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    new_pwd(mysh, pwd);
    free(pwd);
    return mysh->exit_value;
}

int my_cd(struct_mysh_t *mysh)
{
    if (my_array_size(mysh->tab) > 2) {
        my_putstr_error("cd: Too many arguments.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    if (my_array_size(mysh->tab) == 1 || my_strcmp(mysh->tab[1], "~") == 0)
        return home_pwd(mysh);
    if (my_strcmp(mysh->tab[1], "-") == 0)
        return old_pwd(mysh);
    return classic_cd(mysh);
}
