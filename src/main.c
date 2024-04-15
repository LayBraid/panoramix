/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** ex00
*/

#include "panoramix.h"

int main(int ac, char **av)
{
    village_t *my_village = NULL;

    if (!error_handling(ac, av))
        return 84;
    my_village = malloc(sizeof(village_t));
    my_village->nb_villagers = atoi(av[1]);
    my_village->pot_size = atoi(av[2]);
    my_village->nb_fights = atoi(av[3]);
    my_village->nb_refills = atoi(av[4]);
    if (!village(my_village)) {
        free(my_village);
        return 84;
    }
    free(my_village);
    return 0;
}
