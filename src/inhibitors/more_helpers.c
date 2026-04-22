/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** more_helpers.c
*/

#include "../../include/mysh.h"

int separator(char const c, char const *sep, inhibitor_state_t *state)
{
    if (state->in_single_quotes || state->in_double_quotes || state->escaped)
        return 1;
    update_state(state, c);
    for (int i = 0; sep[i] != '\0'; i++) {
        if (c == sep[i])
            return 0;
    }
    return 1;
}

int nb_words(char const *str, char const *sep, inhibitor_state_t *state)
{
    int nb_words = 0;
    int in_word = 0;

    if (!str || str[0] == '\0')
        return 0;
    reset_state(state);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((in_word == 0) && (separator(str[i], sep, state) == 1)) {
            nb_words++;
            in_word = 1;
            continue;
        }
        if (separator(str[i], sep, state) == 0)
            in_word = 0;
    }
    return nb_words;
}

void handle_escaped_char(char current_char, char *array_line, int *row_target,
    inhibitor_state_t *state)
{
    if (is_recognized_escape(current_char)) {
        array_line[*row_target] = get_escaped_char(current_char);
        (*row_target)++;
    } else {
        array_line[*row_target] = '\\';
        (*row_target)++;
        array_line[*row_target] = current_char;
        (*row_target)++;
    }
    state->escaped = 0;
}
