#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
/**
 * This functions are used for sorting algorithms to sort the BusLine array
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;
/**
 * This function create a struct called BusLine which contain 3 fields
 * line number, distance and duration of a line
 */

void bubble_sort (BusLine *start, BusLine *end);
/**
 * This function sort the BusLine array according to the distance of the
 * BusLine, using a bubble sort algorithm.
 * @param start - pointer to the start of the BusLine array
 * @param end - pointer to the end of the BusLine array
 */

void quick_sort (BusLine *start, BusLine *end);
/**
 * This function sort the BusLine array according to the duration of the
 * BusLine, using a quick sort algorithm.
 * @param start - pointer to the start of the BusLine array
 * @param end - pointer to the end of the BusLine array
 */

BusLine *partition (BusLine *start, BusLine *end);
/**
 * This function implements a partition of the quick sort algorithm, sorting
 * the pivot to its sorted place
 * @param start - Pointer to the start of the BusLine array
 * @param end - Pointer to the end of the BusLine array
 * @return The pivot structure in its sorted place according to its duration
 */

void swap (BusLine *swap_loc, BusLine *orig_loc);
/**
 * swap between the pivot original location and its sorted position in the
 * array
 * @param swap_loc - BusLine structure in the sorted location
 * @param orig_loc - BusLine structure in the original location
 */
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
