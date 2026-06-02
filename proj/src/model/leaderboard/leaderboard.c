#include "leaderboard.h"
#include <string.h>

void leaderboard_init(Leaderboard *lb) {
    lb->count = 0;
    memset(lb->records, 0, sizeof(lb->records));
}

void leaderboard_add(Leaderboard *lb, int score) {
    HighScoreRecord entry;
    entry.score = score;

    if (rtc_read_date(&entry.date) != 0) {
        entry.date.day   = 0;
        entry.date.month = 0;
        entry.date.year  = 0;
    }
    if (rtc_read_time(&entry.time) != 0) {
        entry.time.hour   = 0;
        entry.time.minute = 0;
        entry.time.second = 0;
    }

    // Se ainda há espaço, aumenta o count
    if (lb->count < LEADERBOARD_MAX)
        lb->count++;

    // Insere no fim e vai trocando para a posição certa (inserção ordenada)
    int i = lb->count - 1;
    lb->records[i] = entry;

    while (i > 0 && lb->records[i].score > lb->records[i - 1].score) {
        HighScoreRecord tmp   = lb->records[i];
        lb->records[i]        = lb->records[i - 1];
        lb->records[i - 1]    = tmp;
        i--;
    }
}

const HighScoreRecord* leaderboard_get(const Leaderboard *lb, int index) {
    if (index < 0 || index >= lb->count) return NULL;
    return &lb->records[index];
}

int leaderboard_count(const Leaderboard *lb) {
    return lb->count;
}
