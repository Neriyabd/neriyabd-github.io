#include "sort_bus_lines.h"

#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
/**
 * This functions are used to test the program, if it worked as expected
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);
/**
 * This function check if the sorting by distance by bubble sort were
 * successful
 * @param start - A pointer to the start of the BusLine array
 * @param end - A pointer to the start of the BusLine array
 * @return 0 if the array isn't sorted
 * @return 1 if the array was successfully sorted
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);
/**
 * This function check if the sorting by duration by bubble sort were
 * successful
 * @param start - A pointer to the start of the BusLine array
 * @param end - A pointer to the start of the BusLine array
 * @return 0 if the array isn't sorted
 * @return 1 if the array was successfully sorted
 */

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
/**
 * This function check if the original array and the sorted array have the
 * same structures in the array.
 * @param start_sorted - A pointer to the start of the BusLine sorted array
 * @param end_sorted - A pointer to the end of the BusLine sorted array
 * @param start_original - A pointer to the start of the BusLine original array
 * @param end_original - A pointer to the end of the BusLine original array
 * @return FALSE - if the arrays doesn't have the same structures
 * @return TRUE - if the arrays have the same structures
 */
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
