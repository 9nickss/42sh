/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** inhibitor_handling.c
*/

#include "../../include/mysh.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_recognized_escape(char c)
{
    return (c == 'a' || c == 'b' || c == 'e' || c == 'f' ||
            c == 'n' || c == 'r' || c == 't' || c == 'v' ||
            c == '\\' || c == '\'' || c == '\"');
}

void reset_state(inhibitor_state_t *state)
{
    state->escaped = 0;
    state->in_single_quotes = 0;
    state->in_double_quotes = 0;
    state->backslash_count = 0;
}

void update_state(inhibitor_state_t *state, char const c)
{
    if (c == '\'' && !state->escaped && !state->in_double_quotes) {
        state->in_single_quotes = !state->in_single_quotes;
        return;
    }
    if (c == '\"' && !state->escaped && !state->in_single_quotes) {
        state->in_double_quotes = !state->in_double_quotes;
        return;
    }
    if (c == '\\' && !state->escaped) {
        state->escaped = 1;
        return;
    }
    state->escaped = 0;
}

static int skip_to_next_word(char const *str, int i, char const *sep,
    inhibitor_state_t *state)
{
    for (; str[i] != '\0' && (separator(str[i], sep, state) == 0); i++);
    return i;
}

static int len_word(char const *str, int i, char const *sep,
    inhibitor_state_t *state)
{
    int res = 0;

    for (; str[i] != '\0' && (separator(str[i], sep, state) == 1); i++)
        res++;
    return res;
}

int should_keep_inhibitor(char c, inhibitor_state_t *state)
{
    if (state->escaped)
        return 1;
    if (c == '\\') {
        state->backslash_count++;
        if (state->backslash_count % 2 == 0)
            return 1;
        else
            return 0;
    }
    if ((c == '\'' && !state->escaped && !state->in_double_quotes) ||
        (c == '\"' && !state->escaped && !state->in_single_quotes))
        return 0;
    return 1;
}

static int process_tokens(char **array, char const *s, char const *sep,
    inhibitor_state_t *state)
{
    int word_len = 0;
    int word_idx = 0;
    int i = skip_to_next_word(s, 0, sep, state);

    while (s[i] != '\0') {
        word_len = len_word(s, i, sep, state);
        if (word_len == 0) {
            i++;
            continue;
        }
        array[word_idx] = process_word(s, i, word_len, state);
        if (array[word_idx] == NULL)
            return 0;
        word_idx++;
        i = skip_to_next_word(s, i + word_len, sep, state);
    }
    array[word_idx] = NULL;
    return 1;
}

char **inhibitor_parsing(char const *s, char const *sep)
{
    int word_count = 0;
    inhibitor_state_t *state = malloc(sizeof(inhibitor_state_t));
    char **array = NULL;

    if (!s || !sep || !state)
        return NULL;
    array = allocate_result(s, sep, state, &word_count);
    if (!array) {
        free(state);
        return NULL;
    }
    reset_state(state);
    if (!process_tokens(array, s, sep, state)) {
        free(state);
        return NULL;
    }
    free(state);
    return array;
}
