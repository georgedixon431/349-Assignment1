#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "criclist.h"

/*
 * This function is the same as the one from the lab3 code originally
 * found in /courses/compx349/lab3/criclist.c.
 */
static enum country str_to_team(char *team_str) {
    enum country team;

    switch (team_str[0]) {
        case 'A': team = AUS;
                  break;
        case 'B': team = BAN;
                  break;
        case 'E': team = ENG;
                  break;
        case 'I': team = IND;
                  break;
        case 'N': team = NZL;
                  break;
        case 'P': team = PAK;
                  break;
        case 'R': team = RSA;
                  break;
        case 'S': team = SRL;
                  break;
        case 'W': team = WIN;
                  break;
        case 'Z': team = ZIM;
                  break;
        default:  printf("Not a Cricket Playing Nation \n");
                  team = 4;  // New Zealand claims all un-identified players!
    }

    return team;
}


/*
 * This function is from linked lists lecture slide 7.
 */
static CRIC *create_cric(char *name, COUNTRY team, uint16_t matches,
        float bat, float bowl) {
    CRIC *c = (CRIC *)malloc(sizeof(CRIC));

    c->name = strdup(name);
    c->team = team;
    c->played = matches;
    c->bat_avg = bat;
    c->bowl_avg = bowl;
    c->next = NULL;

    return c;
}


/*
 * This function is slightly modified from the lab3 code originally
 * found in /courses/compx349/lab3/criclist.c.
 */
CRIC *enter_player(char *line) {
    char name[41];
    char team[4];
    uint16_t played;
    double bat_avg;
    double bowl_avg;

    if (sscanf(line, "%40[^,],%3[A-Z],%hu,%lf,%lf",
                name, team, &played, &bat_avg, &bowl_avg) != 5) {
        return NULL;
    }

    return create_cric(name, str_to_team(team), played, bat_avg, bowl_avg);
}
