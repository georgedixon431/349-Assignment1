/*
 * This header file is a subset of that used in lab3, originally found
 * in /courses/compx349/lab3/criclist.h.
 */
#ifndef CRICLIST_H_
#define CRICLIST_H_

#include <stdint.h>

typedef enum country {
    AUS, BAN, ENG, IND, NZL, PAK, RSA, SRL, WIN, ZIM
} COUNTRY;

typedef struct cricketer CRIC;

struct cricketer {
    char *name;
    COUNTRY team;
    uint16_t played;
    double bat_avg;
    double bowl_avg;
    CRIC *next;
};

CRIC *enter_player(char *line);

#endif
