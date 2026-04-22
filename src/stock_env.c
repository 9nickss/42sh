/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** stock_env
*/

#include "../include/mysh.h"

void remove_node(linked_list_t **head, const char *value, int size)
{
    linked_list_t *temp = *head;
    linked_list_t *prev = NULL;

    if (!head || !*head)
        return;
    if (temp != NULL && my_strncmp(temp->data, value, size) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && my_strncmp(temp->data, value, size) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

int add_to_list_back(linked_list_t **list, void *data)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));
    linked_list_t *temp = *list;

    if (!new)
        return 84;
    new->data = data;
    new->next = NULL;
    if (*list == NULL) {
        *list = new;
        return 0;
    }
    for (; temp->next != NULL; temp = temp->next);
    temp->next = new;
    return 0;
}

linked_list_t *env_to_ll(char **env)
{
    linked_list_t *list = NULL;
    int error = 0;

    for (int i = 0; env[i] != NULL; i++) {
        error = add_to_list_back(&list, env[i]);
        if (error == 84) {
            free_linked_list(list);
            return NULL;
        }
    }
    return list;
}

char **ll_to_env(linked_list_t *list)
{
    int size = my_list_size(list);
    char **env = malloc(sizeof(char *) * (size + 1));
    linked_list_t *temp = list;

    if (!env)
        return NULL;
    for (int i = 0; i < size; i++) {
        env[i] = malloc(sizeof(char) * (my_strlen(temp->data) + 1));
        if (!env[i]) {
            free_word_array(&env);
            return NULL;
        }
        my_strcpy(env[i], temp->data);
        temp = temp->next;
    }
    env[size] = NULL;
    return env;
}
