/*
** EPITECH PROJECT, 2025
** test
** File description:
** free_shell
*/

#include "../include/mysh.h"

static void free_shell_aliases(void)
{
    alias_t **head = get_alias();

    free_alias_list(*head);
    *head = NULL;
}

static void free_shell_memory(struct_mysh_t *mysh)
{
    if (mysh->old_pwd) {
        free(mysh->old_pwd);
        mysh->old_pwd = NULL;
    }
    if (mysh->tab) {
        free_word_array(&mysh->tab);
        mysh->tab = NULL;
    }
}

static void free_history_components(history_t *history)
{
    if (!history)
        return;
    if (history->cmd)
        free(history->cmd);
    if (history->time)
        free(history->time);
    free(history);
}

void free_history_list(history_t *history)
{
    history_t *current;
    history_t *next;

    if (!history)
        return;
    current = history;
    while (current) {
        next = current->next;
        free_history_components(current);
        current = next;
    }
}

static void free_shell_lists(struct_mysh_t *mysh)
{
    if (mysh->list) {
        free_linked_list(mysh->list);
        mysh->list = NULL;
    }
    if (mysh->local_vars) {
        free_linked_list(mysh->local_vars);
        mysh->local_vars = NULL;
    }
    if (mysh->history) {
        free_history_list(mysh->history);
        mysh->history = NULL;
    }
}

static void free_shell_components(struct_mysh_t *mysh)
{
    free_shell_aliases();
    free_shell_memory(mysh);
    free_shell_lists(mysh);
}

int free_shell(struct_mysh_t *mysh)
{
    int temp = mysh->exit_value;

    free_shell_components(mysh);
    free(mysh);
    mysh = NULL;
    exit(temp);
}
