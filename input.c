#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <threads.h>
#include "criclist.h"
#include "input.h"

extern mtx_t list_mutex; 

/*
 * Read a line of data from the file and create a player based on that data.
 */
static CRIC *read_one_player(FILE *infile) {
    char line[255];

    // read a line, ignoring comments
    do {
        if (fgets(line, sizeof(line), infile) == NULL) {
            return NULL;
        }
    } while (line[0] == '#');

    return enter_player(line);
}

/*
 * Open input file and turn a line of data into a cricketer every second.
 */
int process_input(void *arg) {
    CRIC **head;
    FILE *infile;

    // a pointer to the head of the player list is the single argument
    head = (CRIC **)arg;

    // open the data file for reading
    infile = fopen(PLAYER_DATA_FILE, "r");
    if (infile == NULL) {
        perror("fopen");
        // terminate all threads and stop the whole process
        exit(EXIT_FAILURE);
    }

    while (1) {
        // read data for one player from the file
        CRIC *player = read_one_player(infile);
        if (player == NULL) {
            break;
        }

        mtx_lock(&list_mutex);

        player->next = *head;
        *head = player;

        mtx_unlock(&list_mutex);
       

        sleep(1);
    }
    fclose(infile);
    return 0;
}
