/**
 * @file leaderboard.h
 * @brief High-score leaderboard: stores and ranks the top session scores.
 */

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdint.h>
#include "rtc.h"  /* lab1proj — rtc_date and rtc_time */

#define LEADERBOARD_MAX 5 /**< Maximum number of entries kept in the leaderboard. */

/**
 * @brief A single high-score entry with the timestamp it was achieved.
 */
typedef struct {
    int      score; /**< Score value. */
    rtc_date date;  /**< Calendar date read from the RTC. */
    rtc_time time;  /**< Wall-clock time read from the RTC. */
} HighScoreRecord;

/**
 * @brief Ranked collection of the top high-score records.
 */
typedef struct {
    HighScoreRecord records[LEADERBOARD_MAX]; /**< Records sorted descending by score. */
    int             count;                    /**< Number of valid entries (0–LEADERBOARD_MAX). */
} Leaderboard;

/**
 * @brief Initialises an empty Leaderboard.
 * @param lb Leaderboard to initialise.
 */
void leaderboard_init(Leaderboard *lb);

/**
 * @brief Inserts a new score into the leaderboard, reading the current date/time from the RTC.
 *
 * Scores are kept in descending order. If the leaderboard is full, the lowest
 * existing score is dropped when the new score is higher.
 * @param lb    Leaderboard to update.
 * @param score Score to insert.
 */
void leaderboard_add(Leaderboard *lb, int score);

/**
 * @brief Returns the record at the given rank.
 * @param lb    Leaderboard to query.
 * @param index Rank index (0 = highest score).
 * @return Pointer to the record, or NULL if index is out of range.
 */
const HighScoreRecord* leaderboard_get(const Leaderboard *lb, int index);

/**
 * @brief Returns the number of valid records currently in the leaderboard.
 * @param lb Leaderboard to query.
 * @return Entry count in [0, LEADERBOARD_MAX].
 */
int leaderboard_count(const Leaderboard *lb);

#endif /* LEADERBOARD_H */
