/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** ex00
*/

#include "panoramix.h"

static void help(void)
{
    printf("USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\n");
}

static bool is_number(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
            return (false);
    return (true);
}

bool error_handling(int ac, char **av)
{
    if (ac != 5) {
        help();
        return (false);
    }
    for (int i = 1; i < 5; i++)
        if (!is_number(av[i])) {
            help();
            return (false);
        }
    for (int i = 1; i < 5; i++)
        if (atoi(av[i]) <= 0) {
            help();
            printf("Values must be >0.\n");
            return (false);
        }
    return (true);
}
