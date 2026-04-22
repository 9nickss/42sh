/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** history.c
*/

#include "mysh.h"

int my_history(struct_mysh_t *mysh)
{
    history_t *current = NULL;

    if (!mysh->history)
        return 84;
    current = mysh->history;
    while (current) {
        if (current->cmd)
            printf("\t%d  %s   %s", current->nb, current->time, current->cmd);
        current = current->next;
    }
    return 0;
}

static char *add_time(void)
{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char time_buffer[100];
    char *result;

    strftime(time_buffer, sizeof(time_buffer), "%H:%M", local_time);
    result = strdup(time_buffer);
    if (result)
        return result;
    return NULL;
}

void init_new_node(history_t *new_node, const char *cmd)
{
    new_node->cmd = strdup(cmd);
    new_node->time = add_time();
}

static int check_new_node(history_t *new_node)
{
    if (!new_node->time)
        return 84;
    if (!new_node->cmd) {
        free(new_node);
        return 84;
    }
    return 0;
}

static history_t *create_history_node(const char *cmd)
{
    history_t *new_node;

    if (!cmd)
        return NULL;
    new_node = malloc(sizeof(history_t));
    if (!new_node)
        return NULL;
    init_new_node(new_node, cmd);
    if (check_new_node(new_node) == 84)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

history_t *add_to_history(const char *cmd, history_t *history)
{
    history_t *current = NULL;
    history_t *new_node = create_history_node(cmd);

    if (!new_node)
        return NULL;
    if (!history) {
        new_node->nb = 1;
        return new_node;
    }
    current = history;
    new_node->nb = 2;
    while (current->next) {
        current = current->next;
        new_node->nb++;
    }
    current->next = new_node;
    return history;
}
