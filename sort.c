#include <stdlib.h>
#include <time.h>
#include <threads.h>
#include <string.h>
#include "criclist.h"
#include "sort.h"

extern mtx_t list_mutex;

int process_sort(void *arg) {
    CRIC **head = (CRIC **)arg;

    srand((unsigned int)time(NULL));

    while (1) {
        int delay_ms = 500 + rand() % 501;

        struct timespec delay;
        delay.tv_sec = delay_ms / 1000;
        delay.tv_nsec = (delay_ms % 1000) * 1000000L;

        thrd_sleep(&delay, NULL);

        mtx_lock(&list_mutex);

        CRIC *current = *head;

        while (current != NULL && current->next != NULL) {

            if (strcmp(current->name, current->next->name) > 0) {
                // swap player data
            }

            current = current->next;
        }

        mtx_unlock(&list_mutex);
    }

    return 0;
}