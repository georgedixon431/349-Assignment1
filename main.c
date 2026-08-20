#include <stdio.h>
#include <threads.h> 
#include <stdlib.h>
#include "criclist.h"
#include "input.h"
#include "sort.h"


mtx_t list_mutex; //Shared mutex used to protect the linked list and running flag
int running = 1; //to tell input and sort when to stop

int main(void) {
    CRIC *head = NULL;
    

    // TODO: start the reading/input thread
    // e.g. thrd_create()
    if (mtx_init(&list_mutex, mtx_plain) != thrd_success) {
        printf("Failed to initialise mutex\n");
        return 1;
    } //Initialise the mutex before creating any worker threads

    thrd_t input_thread; //start input thread
    if (thrd_create(&input_thread, process_input, &head) != thrd_success) {
        printf("Failed to create input thread\n");
        return 1;
    }

    // TODO: start the sorting thread
    // e.g. thrd_create()
    thrd_t sort_thread; //Start the sorting thread
    if (thrd_create(&sort_thread, process_sort, &head) != thrd_success){
        printf("Failed to create sorting thread\n");
        // Tell the input thread to stop before cleaning up
        mtx_lock(&list_mutex);
        running = 0;
        mtx_unlock(&list_mutex);
        thrd_join(input_thread, NULL);
        mtx_destroy(&list_mutex);

        return 1;
    }
    
    // TODO: loop forever until user presses 'q'
    // TODO: print the list if any other key is pressed
    char input;

    //wait for keyboard input
    while (1){
        input = getchar();

        // Stop cleanly if standard input is closed
        if (input == EOF) {
            mtx_lock(&list_mutex);
            running = 0;
            mtx_unlock(&list_mutex);
            break;
        }
        if (input =='\n'){ //ignore newline when enter pressed
            continue;
        }
        if (input == 'q'){ //q tells program to stop
            running =0;
            break;
        }
        mtx_lock(&list_mutex); //lock list while printing
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

    // Wait for both threads to finish
    thrd_join(input_thread, NULL);
    printf("Input thread stopped\n");
    thrd_join(sort_thread, NULL);
    printf("Sort thread stopped\n");

    // Free all players in the linked list
    CRIC *current = head;
    
    while (current != NULL) {
        CRIC *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    // Clean up the mutex
    mtx_destroy(&list_mutex);
    printf("Mutex destroyed\n");


    return 0;
}
