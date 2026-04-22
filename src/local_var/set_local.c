/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** set_local.c
*/

#include "../../include/mysh.h"

static int validate_var_name(const char *var_name, struct_mysh_t *mysh)
{
    if (!(var_name[0] >= 'A' && var_name[0] <= 'Z') &&
        !(var_name[0] >= 'a' && var_name[0] <= 'z') &&
        !(var_name[0] == '_')) {
        my_putstr_error("set: Variable name must begin with a letter.\n");
        mysh->exit_value = 1;
        return 1;
    }
    return 0;
}

static int create_and_add_var(char *var_name,
    char *var_value, struct_mysh_t *mysh)
{
    char *new_var = malloc(my_strlen(var_name) + my_strlen(var_value) + 2);

    if (!new_var)
        return 1;
    my_strcpy(new_var, var_name);
    my_strcat(new_var, "=");
    my_strcat(new_var, var_value);
    add_to_list_back(&mysh->local_vars, new_var);
    return 0;
}

static int check_set_args(struct_mysh_t *mysh)
{
    if (my_array_size(mysh->tab) == 1)
        return print_local_vars(mysh);
    if (!mysh->tab[1] || strchr(mysh->tab[1], '=') == NULL) {
        my_putstr_error("set: Variable must be in format 'name=value'\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    return -1;
}

static char *parse_var_name(struct_mysh_t *mysh, char **var_value)
{
    char *var_name = strdup(mysh->tab[1]);
    char *equals;

    if (!var_name)
        return NULL;
    equals = strchr(var_name, '=');
    *equals = '\0';
    *var_value = equals + 1;
    return var_name;
}

static int update_existing_var(struct_mysh_t *mysh, char *var_name)
{
    char **str = parse_local_var(mysh, var_name, my_strlen(var_name));

    if (str != NULL) {
        remove_node(&mysh->local_vars, var_name, my_strlen(var_name));
        free_word_array(&str);
    }
    return 0;
}

int my_set(struct_mysh_t *mysh)
{
    char *var_name;
    char *var_value;
    int check_result = check_set_args(mysh);

    if (check_result != -1)
        return check_result;
    var_name = parse_var_name(mysh, &var_value);
    if (!var_name)
        return 1;
    if (validate_var_name(var_name, mysh)) {
        free(var_name);
        return mysh->exit_value;
    }
    update_existing_var(mysh, var_name);
    if (create_and_add_var(var_name, var_value, mysh)) {
        free(var_name);
        return 1;
    }
    free(var_name);
    return mysh->exit_value;
}

int my_unset(struct_mysh_t *mysh)
{
    char **str = NULL;

    if (my_array_size(mysh->tab) < 2) {
        my_putstr_error("unset: Too few arguments.\n");
        mysh->exit_value = 1;
        return mysh->exit_value;
    }
    for (int i = 1; mysh->tab[i] != NULL; i++) {
        str = parse_local_var(mysh, mysh->tab[i], my_strlen(mysh->tab[i]));
        if (str != NULL) {
            remove_node(&mysh->local_vars, mysh->tab[i],
                my_strlen(mysh->tab[i]));
            free_word_array(&str);
        }
    }
    return mysh->exit_value;
}
