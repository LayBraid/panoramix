/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** ex00
*/


#ifndef PANORAMIX_PANORAMIX_H
    #define PANORAMIX_PANORAMIX_H

    #include "stdbool.h"
    #include "stdio.h"
    #include "stdlib.h"
    #include <unistd.h>
    #include <pthread.h>
    #include <semaphore.h>

    #define LOCK_PRINTF(village, str, ...) { \
        pthread_mutex_lock(&village->printer); \
        printf(str, __VA_ARGS__); \
        pthread_mutex_unlock(&village->printer); \
}

    #define LOCK_WRITE(village, str, ...) { \
        pthread_mutex_lock(&village->printer); \
        printf(str); \
        pthread_mutex_unlock(&village->printer); \
}

typedef struct village village_t;
typedef struct villager villager_t;

struct villager {
    int id;
    pthread_t thread;
    village_t *village;
};

struct village {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    sem_t emptyPot;
    sem_t fullPot;
    pthread_mutex_t distribution;
    pthread_mutex_t printer;
    int potions;
    pthread_t *druid;
};

bool error_handling(int ac, char **av);

int village(village_t *my_village);

#endif //PANORAMIX_PANORAMIX_H
