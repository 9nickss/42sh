/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** inhibitor_helpers.c
*/

#include "../../include/mysh.h"

char get_escaped_char(char c)
{
    char escaped_chars[256] = {0};

    escaped_chars['a'] = '\a';
    escaped_chars['b'] = '\b';
    escaped_chars['e'] = '\033';
    escaped_chars['f'] = '\f';
    escaped_chars['n'] = '\n';
    escaped_chars['r'] = '\r';
    escaped_chars['t'] = '\t';
    escaped_chars['v'] = '\v';
    escaped_chars['\\'] = '\\';
    escaped_chars['\''] = '\'';
    escaped_chars['\"'] = '\"';
    return escaped_chars[(unsigned char)c] ?
        escaped_chars[(unsigned char)c] : c;
}

void handle_quote_char(char current_char, inhibitor_state_t *state)
{
    if (current_char == '\'' && !state->in_double_quotes)
        state->in_single_quotes = !state->in_single_quotes;
    else if (current_char == '\"' && !state->in_single_quotes)
        state->in_double_quotes = !state->in_double_quotes;
}

char *process_word(char const *s, int start_idx, int word_len,
    inhibitor_state_t *state)
{
    int row_target = 0;
    char *word = malloc(sizeof(char) * (word_len * 2 + 1));

    if (word == NULL)
        return NULL;
    reset_state(state);
    for (int row = 0; row < word_len; row++)
        process_char(s[start_idx + row], word, &row_target, state);
    word[row_target] = '\0';
    return word;
}

void process_char(char current_char, char *array_line, int *row_target,
    inhibitor_state_t *state)
{
    if (current_char == '\n')
        return;
    if (current_char == '\\' && !state->escaped) {
        state->escaped = 1;
        return;
    }
    if (state->escaped) {
        handle_escaped_char(current_char, array_line, row_target, state);
        return;
    }
    if ((current_char == '\'' && !state->in_double_quotes) ||
        (current_char == '\"' && !state->in_single_quotes)) {
        handle_quote_char(current_char, state);
        return;
    }
    array_line[*row_target] = current_char;
    *row_target += 1;
}

char **allocate_result(char const *s, char const *sep,
    inhibitor_state_t *state, int *word_count)
{
    *word_count = nb_words(s, sep, state);
    return malloc(sizeof(char *) * (*word_count + 1));
}
