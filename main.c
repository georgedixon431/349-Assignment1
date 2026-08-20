#include <stdio.h>
#include <threads.h> 
#include "criclist.h"
#include "input.h"
#include "sort.h"

mtx_t list_mutex;

int main(void) {
    CRIC *head = NULL;
    

    // TODO: start the reading/input thread
    mtx_init(&list_mutex, mtx_plain);
    thrd_t input_thread;
    if (thrd_create(&input_thread, process_input, &head) != thrd_success) {
        printf("Failed to create input thread\n");
        return 1;
    }
    // e.g. thrd_create()

    // TODO: start the sorting thread
    // e.g. thrd_create()
    thrd_t sort_thread;
    if (thrd_create(&sort_thread, process_sort, &head) != thrd_success){
        printf("Failed to create sorting thread\n");
        return 1;
    }


    // TODO: loop forever until user presses 'q'
    // TODO: print the list if any other key is pressed
    char input;

    while (1){
        input = getchar();
        if (input =='\n'){
            continue;
        }
        if (input == 'q'){
            break;
        }
        mtx_lock(&list_mutex);
        //linked list
        CRIC *current = head;
        while(current != NULL){
            printf("%s, %d, %u, %.2f, %.2f\n",
                    current->name,
                    current->team,
                    current->played,
                    current->bat_avg,
                    current->bowl_avg);
            current = current ->next;
        }
        mtx_unlock(&list_mutex);
    }


    return 0;
}
