/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** local_var_utils.c - Utility functions for local variables
*/

#include "../../include/mysh.h"

char *find_in_list(linked_list_t *list, const char *var_name, int name_len)
{
    linked_list_t *current = list;
    char *name;

    while (current != NULL) {
        name = (char *)current->data;
        if (strncmp(name, var_name, name_len) == 0 && name[name_len] == '=') {
            return name + name_len + 1;
        }
        current = current->next;
    }
    return NULL;
}

char *get_var_value(struct_mysh_t *mysh, const char *var_name)
{
    char *value;
    int name_len = my_strlen(var_name);

    value = find_in_list(mysh->local_vars, var_name, name_len);
    if (value)
        return value;
    return find_in_list(mysh->list, var_name, name_len);
}

static char **create_result_array(const char *data)
{
    char **result = NULL;
    char *temp = NULL;

    temp = my_strdup(data);
    if (!temp)
        return NULL;
    result = malloc(sizeof(char *) * 2);
    if (!result) {
        free(temp);
        return NULL;
    }
    result[0] = temp;
    result[1] = NULL;
    return result;
}

char **parse_local_var(struct_mysh_t *mysh, char *id, int size)
{
    linked_list_t *current = mysh->local_vars;
    char **result = NULL;

    while (current != NULL) {
        if (strncmp(current->data, id, size) == 0 &&
            ((char *)current->data)[size] == '=') {
            result = create_result_array(current->data);
            return result;
        }
        current = current->next;
    }
    return NULL;
}
