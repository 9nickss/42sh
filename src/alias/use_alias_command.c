/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include "../../include/mysh.h"

static char *get_alias_command(alias_t *head, char *name, int depth)
{
    alias_t *current = head;

    if (depth > 10) {
        fprintf(stderr, "Alias loop detected for '%s'\n", name);
        return NULL;
    }
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return get_alias_command(head, current->command, depth + 1);
        }
        current = current->next;
    }
    return name;
}

int resolve_and_update_alias(struct_mysh_t *mysh, alias_t **head, char *line)
{
    char *alias_command = NULL;
    char **new_tab = NULL;

    mysh->tab = inhibitor_parsing(line, " \"\t\\");
    if (!mysh->tab)
        return 0;
    alias_command = get_alias_command(*head, mysh->tab[0], 0);
    if (alias_command && strcmp(alias_command, mysh->tab[0]) != 0) {
        new_tab = my_str_to_word_array(alias_command, " ");
        if (!new_tab)
            return 1;
        free_word_array(&mysh->tab);
        mysh->tab = new_tab;
    }
    return 0;
}
