/*
** EPITECH PROJECT, 2024
** Power
** File description:
** Return the power with 2 param nb and p
*/

int my_compute_power_rec(int nb, int p)
{
    int result = 1;

    if (p == 0) {
        return 1;
    }
    if (p < 0 || p > 31 || nb > 2147483647) {
        return 0;
    }
    result = nb * my_compute_power_rec(nb, p - 1);
    return result;
}
