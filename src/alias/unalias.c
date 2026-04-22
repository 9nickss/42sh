/*
** EPITECH PROJECT, 2025
** unalias
** File description:
** delete an alias or more
*/

#include "../../include/mysh.h"

static void free_alias(alias_t **head, alias_t *current, alias_t *prev)
{
    if (prev == NULL)
        *head = current->next;
    else
        prev->next = current->next;
    free(current->name);
    free(current->command);
    free(current);
}

static void remove_alias(alias_t **head, const char *name)
{
    alias_t *current = *head;
    alias_t *prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            free_alias(head, current, prev);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int my_unalias(struct_mysh_t *mysh)
{
    alias_t **head = get_alias();

    if (!mysh->tab[1])
        return 1;
    if (my_strcmp(mysh->tab[1], "*") == 0) {
        if (*head) {
            free_alias_list(*head);
            *head = NULL;
            printf("[DEBUG] Alias list cleared, head = %p\n", (void *)*head);
        }
        return 0;
    }
    for (int i = 1; mysh->tab[i]; i++)
        remove_alias(head, mysh->tab[i]);
    return 0;
}
