/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** ex00
*/

#include "panoramix.h"

static void *druid(village_t *my_village)
{
    int nb_refills = my_village->nb_refills;

    LOCK_WRITE(my_village, "Druid: I'm ready... but sleepy...\n")
    while (nb_refills) {
        sem_wait(&my_village->emptyPot);
        LOCK_PRINTF(my_village,
            "Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I "
            "can only make %d more refills after this one.\n",
            nb_refills - 1);
        my_village->potions += my_village->pot_size;
        sem_post(&my_village->fullPot);
        nb_refills--;
    }
    LOCK_WRITE(my_village,
        "Druid: I'm out of viscum. I'm going back to... zZz\n")
    return NULL;
}

static void intern_villager(villager_t *my_villager, int *fight)
{
    LOCK_PRINTF(my_villager->village,
        "Villager %d: I need a drink... I see %d servings left.\n",
        my_villager->id, my_villager->village->potions)
    pthread_mutex_lock(&my_villager->village->distribution);
    if (my_villager->village->potions == 0) {
        LOCK_PRINTF(my_villager->village,
            "Villager %d: Hey Pano wake up! We need more potion.\n",
            my_villager->id)
        sem_post(&my_villager->village->emptyPot);
        sem_wait(&my_villager->village->fullPot);
    }
    my_villager->village->potions--;
    pthread_mutex_unlock(&my_villager->village->distribution);
    (*fight)--;
    LOCK_PRINTF(my_villager->village,
        "Villager %d: Take that roman scum! Only %d left.\n",
        my_villager->id, *fight)
    sleep(1);
}

static int villager(villager_t *my_villager)
{
    int fight = my_villager->village->nb_fights;

    LOCK_PRINTF(my_villager->village, "Villager %d: Going into battle!\n",
        my_villager->id)
    while (fight)
        intern_villager(my_villager, &fight);
    LOCK_PRINTF(my_villager->village, "Villager %d: I'm going to sleep now.\n",
        my_villager->id)
    return 0;
}

static void setup_village(village_t *my_village)
{
    my_village->potions = my_village->pot_size;
    pthread_mutex_init(&my_village->distribution, NULL);
    pthread_mutex_init(&my_village->printer, NULL);
    sem_init(&my_village->emptyPot, 0, 0);
    sem_init(&my_village->fullPot, 0, 0);
    my_village->druid = malloc(sizeof(pthread_t));
}

int village(village_t *my_village)
{
    villager_t villagers[my_village->nb_villagers];

    setup_village(my_village);
    pthread_create(my_village->druid, NULL, (void *) druid, my_village);
    for (int i = 0; i < my_village->nb_villagers; i++) {
        villagers[i].id = i;
        villagers[i].village = my_village;
        pthread_create(&villagers[i].thread, NULL,
            (void *) villager, &villagers[i]);
    }
    for (int i = 0; i < my_village->nb_villagers; i++)
        pthread_join(villagers[i].thread, NULL);
    free(my_village->druid);
    return 1;
}
