/*
** EPITECH PROJECT, 2024
** String copy
** File description:
** Copy a string into another param
*/

char *my_strcpy(char *dest, char *src)
{
    int count_char = 0;

    while (src[count_char] != '\0') {
        dest[count_char] = src[count_char];
        count_char++;
    }
    dest[count_char] = '\0';
    return dest;
}
