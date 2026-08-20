#include <stdlib.h>
#include <time.h>
#include <threads.h>
#include <string.h>
#include "criclist.h"
#include "sort.h"

//shared variables
extern int running;
extern mtx_t list_mutex;

int process_sort(void *arg) {
    CRIC **head = (CRIC **)arg;
    //seed for rand number
    srand((unsigned int)time(NULL));

    while (1) {
        //sleep for 500-1000ms then one bubble-sort pass over shared list
        int delay_ms = 500 + rand() % 501;
        struct timespec delay;
        delay.tv_sec = delay_ms / 1000;
        delay.tv_nsec = (delay_ms % 1000) * 1000000L;

        thrd_sleep(&delay, NULL);

        //hold mutex while sorting list
        mtx_lock(&list_mutex);

        //stop if q
        if (!running){
            mtx_unlock(&list_mutex);
            break;
        }

        //current points to the pointer that leads to the first node in the pair currently being compared.
        CRIC **current = head;

        while (*current != NULL && (*current)->next != NULL) {

            CRIC *first = *current;
            CRIC *second = first->next;

            //Swap adjacent nodes if they are in the wrong alphabetical order.
            if (strcmp(first->name, second->name) > 0) {
                first->next = second->next;
                second->next = first;
                *current = second;
            }
            //move to next pair of nodes
            current = &((*current)->next);
        }

        mtx_unlock(&list_mutex);
    }

    return 0;
}