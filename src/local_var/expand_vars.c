/*
** EPITECH PROJECT, 2024
** B-PSU-200-NCE-2-1-42sh-gabriel.spanneut-peressutti
** File description:
** expand_vars.c
*/

#include "../../include/mysh.h"

static int is_var_char(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') || c == '_')
        return 1;
    return 0;
}

static int extract_var_name(const char *str, int start, char *var_name)
{
    int i = start;
    int j = 0;

    while (str[i] && is_var_char(str[i])) {
        var_name[j] = str[i];
        i = i + 1;
        j = j + 1;
    }
    var_name[j] = '\0';
    return i - start;
}

static int copy_var_value(struct_mysh_t *mysh, char *var_name,
    char *result, int j)
{
    char *value = get_var_value(mysh, var_name);

    if (value) {
        strcpy(&result[j], value);
        j = j + strlen(value);
    }
    return j;
}

static int handle_dollar_sign(struct_mysh_t *mysh, expand_state_t *state)
{
    char var_name[256];
    int var_len;

    state->i = state->i + 1;
    var_len = extract_var_name(state->str, state->i, var_name);
    if (var_len > 0) {
        state->j = copy_var_value(mysh, var_name, state->result, state->j);
        state->i = state->i + var_len;
    }
    return state->j;
}

static int handle_regular_char(expand_state_t *state)
{
    state->result[state->j] = state->str[state->i];
    state->j = state->j + 1;
    state->i = state->i + 1;
    return state->j;
}

char *expand_string_vars(struct_mysh_t *mysh, const char *str)
{
    expand_state_t state;

    state.str = str;
    state.result = malloc(strlen(str) * 2 + 1);
    state.i = 0;
    state.j = 0;
    if (!state.result)
        return NULL;
    while (state.str[state.i]) {
        if (state.str[state.i] == '$' && state.str[state.i + 1]) {
            state.j = handle_dollar_sign(mysh, &state);
        } else {
            state.j = handle_regular_char(&state);
        }
    }
    state.result[state.j] = '\0';
    return state.result;
}

void expand_command_vars(struct_mysh_t *mysh)
{
    char *expanded;
    int i = 0;

    if (!mysh->tab)
        return;
    while (mysh->tab[i] != NULL) {
        expanded = expand_string_vars(mysh, mysh->tab[i]);
        if (expanded) {
            free(mysh->tab[i]);
            mysh->tab[i] = expanded;
        }
        i = i + 1;
    }
}
