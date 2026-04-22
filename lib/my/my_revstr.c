/*
** EPITECH PROJECT, 2024
** Reverse string
** File description:
** Reverse the string in param (nb)
*/

char *my_revstr(char *str)
{
    char tempo;
    int count_left = 0;
    int count_right = 0;

    while (str[count_right] != '\0') {
        count_right++;
    }
    count_right--;
    while (count_left < count_right) {
        tempo = str[count_left];
        str[count_left] = str[count_right];
        str[count_right] = tempo;
        count_left++;
        count_right--;
    }
    return str;
}
