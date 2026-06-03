#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdint.h>
#include "rtc.h"  // lab1proj — rtc_date e rtc_time

#define LEADERBOARD_MAX 5

typedef struct {
    int score;
    rtc_date date;
    rtc_time time;
} HighScoreRecord;

typedef struct {
    HighScoreRecord records[LEADERBOARD_MAX];
    int count;  // número de registos válidos (0 a LEADERBOARD_MAX)
} Leaderboard;

void leaderboard_init(Leaderboard *lb);

// Lê data e hora do RTC e insere o score ordenado (maior para menor)
// Descarta o registo mais baixo se já estiver cheio
void leaderboard_add(Leaderboard *lb, int score);

// Devolve o registo na posição index (0 = melhor score)
const HighScoreRecord* leaderboard_get(const Leaderboard *lb, int index);

int leaderboard_count(const Leaderboard *lb);

#endif /* LEADERBOARD_H */
