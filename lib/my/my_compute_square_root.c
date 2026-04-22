/*
** EPITECH PROJECT, 2024
** Square root
** File description:
** Return the square root of param nb
*/

int my_compute_square_root(int nb)
{
    int result = 1;

    if (nb <= 0) {
        return 0;
    }
    while (result <= nb) {
        if (result > nb / 2) {
            return 0;
        }
        if (nb == result * result) {
            return result;
        }
        result++;
    }
}
