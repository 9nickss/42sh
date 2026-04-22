/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** local_var_display.c
*/

#include "../../include/mysh.h"

static int get_name_length(char *data)
{
    char *equals = strchr(data, '=');

    if (!equals)
        return 0;
    return equals - data;
}

int find_max_name_length(linked_list_t *list)
{
    linked_list_t *current = list;
    int max_name_len = 0;
    int name_len = 0;

    while (current != NULL) {
        name_len = get_name_length((char *)current->data);
        if (name_len > max_name_len)
            max_name_len = name_len;
        current = current->next;
    }
    return max_name_len;
}

void print_formatted_var(char *data, int max_name_len)
{
    char *equals = strchr(data, '=');
    int name_len;

    if (equals) {
        *equals = '\0';
        my_putstr(data);
        name_len = equals - data;
        for (int i = 0; i < max_name_len - name_len + 4; i++)
            my_putchar(' ');
        my_putstr(equals + 1);
        my_putchar('\n');
        *equals = '=';
    } else {
        my_putstr(data);
        my_putchar('\n');
    }
}

int print_local_vars(struct_mysh_t *mysh)
{
    linked_list_t *current = mysh->local_vars;
    int max_name_len;

    if (!current) {
        my_putstr("No local variables defined\n");
        return mysh->exit_value;
    }
    max_name_len = find_max_name_length(mysh->local_vars);
    current = mysh->local_vars;
    while (current != NULL) {
        print_formatted_var(current->data, max_name_len);
        current = current->next;
    }
    return mysh->exit_value;
}

int print_all_vars(struct_mysh_t *mysh)
{
    linked_list_t *current;

    current = mysh->local_vars;
    while (current != NULL) {
        my_putstr(current->data);
        my_putchar('\n');
        current = current->next;
    }
    return mysh->exit_value;
}
