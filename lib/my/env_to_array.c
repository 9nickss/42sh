/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env_to_array
*/

#include "my.h"
#include "../../include/mylist.h"

char **env_list_to_array(linked_list_t *envnode)
{
    char **env_array;
    int count;
    linked_list_t *current = envnode;

    count = my_list_size(envnode);
    env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;
    for (int i = 0; i < count; i++) {
        env_array[i] = my_strdup((char *)current->data);
        if (!env_array[i]) {
            free_word_array(&env_array);
            return NULL;
        }
        current = current->next;
    }
    env_array[count] = NULL;
    return env_array;
}
