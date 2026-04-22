/*
** EPITECH PROJECT, 2024
** B-CPE-110-NCE-1-1-settingup-jules.martins
** File description:
** my_str_to_word_array
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

int my_sep(char const c, char const *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (c == sep[i])
            return 0;
    }
    return 1;
}

int stwrd(char const *str, int i, char const *sep)
{
    for (; str[i] != '\0' && (my_sep(str[i], sep) == 0); i++);
    return i;
}

int len_word(char const *str, int i, char const *sep)
{
    int res = 0;

    for (; str[i] != '\0' && (my_sep(str[i], sep) == 1); i++)
        res++;
    return res;
}

int nb_word(char const *str, char const *sep)
{
    int nb_word = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((in_word == 0) && (my_sep(str[i], sep) == 1)) {
            nb_word++;
            in_word = 1;
            continue;
        }
        if (my_sep(str[i], sep) == 0)
            in_word = 0;
    }
    return nb_word;
}

char **my_str_to_word_array(char const *s, char const *sep)
{
    int len = 0;
    int row = 0;
    int line = 0;
    char **array = malloc(sizeof(char *) * (nb_word(s, sep) + 1));

    if (!s | !sep | !array)
        return NULL;
    for (int i = stwrd(s, 0, sep); s[i] != '\0'; i = stwrd(s, i + len, sep)) {
        len = len_word(s, i, sep);
        array[line] = malloc(sizeof(char) * (len + 1));
        if (array[line] == NULL)
            return NULL;
        for (row = 0; row < len; row++)
            array[line][row] = s[i + row];
        array[line][row] = '\0';
        line++;
    }
    array[line] = NULL;
    return array;
}
