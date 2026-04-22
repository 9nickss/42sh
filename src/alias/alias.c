/*
** EPITECH PROJECT, 2025
** alias
** File description:
** make the alias
*/

#include "../../include/mysh.h"

alias_t **get_alias(void)
{
    static alias_t *head = NULL;

    return &head;
}

void print_alias_list(alias_t *head)
{
    alias_t *current = head;

    while (current != NULL) {
        if (current->name && current->command)
            printf("%s\t%s\n", current->name, current->command);
        current = current->next;
    }
}

static alias_t *create_node(char *name, char *command)
{
    alias_t *new_node = malloc(sizeof(alias_t));

    if (!new_node)
        return NULL;
    new_node->name = strdup(name);
    new_node->command = strdup(command);
    if (!new_node->name || !new_node->command) {
        free(new_node->name);
        free(new_node->command);
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

int add_node(alias_t **head, char *name, char *command)
{
    alias_t *current = *head;
    alias_t *new_node;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            free(current->command);
            current->command = strdup(command);
            return current->command ? 0 : 84;
        }
        current = current->next;
    }
    new_node = create_node(name, command);
    if (!new_node)
        return 84;
    new_node->next = *head;
    *head = new_node;
    return 0;
}

void free_alias_list(alias_t *head)
{
    alias_t *current = head;
    alias_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->name);
        free(current->command);
        free(current);
        current = next;
    }
}

static int get_command(struct_mysh_t *mysh, char **command, char *temp, int i)
{
    if (*command == NULL) {
        *command = strdup(mysh->tab[i]);
        if (!*command)
            return 84;
    } else {
        temp = *command;
        *command = malloc(strlen(temp) + strlen(mysh->tab[i]) + 2);
        if (!*command) {
            free(temp);
            return 84;
        }
        sprintf(*command, "%s %s", temp, mysh->tab[i]);
        free(temp);
    }
    return 0;
}

static int display_alias_command(alias_t *head, const char *name)
{
    alias_t *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("%s\n", current->command);
            return 0;
        }
        current = current->next;
    }
    return 0;
}

int my_alias(struct_mysh_t *mysh)
{
    alias_t **head = get_alias();
    char *command = NULL;
    char *temp = NULL;

    if (!mysh->tab[1]) {
        print_alias_list(*head);
        return 0;
    }
    if (!mysh->tab[2])
        return display_alias_command(*head, mysh->tab[1]);
    for (int i = 2; mysh->tab[i]; i++)
        get_command(mysh, &command, temp, i);
    if (add_node(head, mysh->tab[1], command) == 84) {
        free(command);
        return 84;
    }
    free(command);
    return 0;
}
