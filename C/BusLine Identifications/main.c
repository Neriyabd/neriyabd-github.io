#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define ARG2 2
#define NUM_OF_ARGUMENTS 3
#define MIN_LINES 1
#define MAX_LINES 999
#define MIN_DIST 0
#define MAX_DIST 1000
#define MIN_DURA 10
#define MAX_DURA 100
#define BUFFER_LENGTH 10
#define INPUT_BUFFER 61
#define BUBBLE "bubble"
#define QUICK "quick"
#define TEST "test"
#define TEST1 "TEST 1"
#define TEST2 "TEST 2"
#define TEST3 "TEST 3"
#define TEST4 "TEST 4"
#define LINE_INFO_MSG "Enter line info. Then enter\n"
#define ARGS_ERROR_MSG "USAGE: Use one of those modes: %s %s and %s\n"
#define TEST_1_PASSED_MSG "%s PASSED: testing the array is sorted by \
distance\n"
#define TEST_1_FAILED_MSG "%s FAILED: The array isn't sorted by distance\n"
#define TEST_2_PASSED_MSG "%s PASSED: testing the array have the same items \
after sorting\n"
#define TEST_2_FAILED_MSG "%s FAILED: The array doesn't have the same items \
after sorting\n"
#define TEST_3_PASSED_MSG "%s PASSED: testing the array is sorted by \
duration\n"
#define TEST_3_FAILED_MSG "%s FAILED: The array isn't sorted by duration\n"
#define TEST_4_PASSED_MSG "%s PASSED: testing the array have the same items \
after sorting\n"
#define TEST_4_FAILED_MSG "%s FAILED: The array doesn't have the same items \
after sorting\n"
#define NUM_LINES_INPUT_MSG "Enter number of lines. Then enter\n"
#define ERROR_NUM_LINES_MSG "ERROR: Number of lines should be a positive \
integer\n"
#define ERROR_DURATION_RANGE_MSG "ERROR: duration should be an integer \
between %d and %d (includes)\n"
#define ERROR_LINE_NUMBER_RANGE_MSG "ERROR: distance should be an integer \
between %d and %d (includes)\n"
#define DISTANCE_ERROR_MSG "ERROR: Line number should be an integer between \
%d and %d (includes)\n"

/**
 * This program gets a number of lines and information about the lines in
 * this form: (line number, distance, duration).
 * The program sort the number of lines based on the argument given by the
 * user, and prints the sorted lines in an order.
 * The program can test itself, with a test argument and check if the sorting
 * worked as expected
 */



int number_of_lines ();
/**
 * Get an input from the user to the number of BusLine structures to add the
 * BusLine array
 * @param num_lines - An int that represents the number of lines in an
 * BusLine array
 * @return TRUE - if the input failed
 * @return FALSE - if the input was implemented successfully
 */

bool testing_cases (int num_lines, BusLine *arr);
/**
 * This function allocate memory for copies of a BusLine array and perform
 * tests check on the program
 * @param num_lines - An int that represent the number of lines in the
 * BusLine arrays
 * @param arr - A pointer to a BusLine struct array
 * @return FALSE - if the memory allocation wasn't successful
 * @return TRUE - if the memory allocation was successful
 */

void add_busline (BusLine *arr, int num_lines);
/**
 * Get an input from the user and add it into a BusLine structure
 * @param arr - A pointer to the first element in the BusLine array
 * @param num_lines - An int that represents the number of lines in an
 * BusLine array
 */

bool valid_args (char argument[]);
/**
 * Check for a valid argument from the user
 * @param argument - argument from the user
 * @return FALSE for an incorrect input
 * @return TRUE for a correct input
 */

void run_tests (BusLine *start_original, BusLine *end_original,
                BusLine *dis_start, BusLine *dis_end, BusLine
                *dur_start, BusLine *dur_end);
/**
 * This function applies the test to check the validity of functions in
 * the program
 * @param start_sorted - A pointer to the first element of the BusLine
 * original array
 * @param end_sorted - A pointer to the last element of the BusLine
 * original array
 * @param start_original - A pointer to the first element of the BusLine
 * copied array
 * @param end_original - A pointer to the last element of the BusLine
 * copied array
 */

bool valid_input_value (int line_number, int distance, int duration);
/**
* Check for a correct input number for line number, distance and duration.
* @param line_number - An int that represent the line number of the BusLine
* @param distance - An int that represent the line distance of the BusLine
* @param duration - An int that represent the line number of the BusLine
* @return - FALSE if the parameter is not in valid range
* @return - TRUE if the parameter is in valid range
*/

void print_array (int num_lines, BusLine *start);
/**
* This function prints line number, distance and duration of a BusLine array.
* @param counter - A counter to the length of the array
* @param start - Pointer to the first element of the BusLine array
*/

bool process_command (BusLine *arr, char arg[], int num_lines);
/**
 * check the mode to apply to the program to use based on the variable arg
 * and check if the operation was successful
 * @param arr - A pointer to a BusLine struct array
 * @param arg - The argument from the user
 * @param num_lines - An int that represent the number of lines in the
 * BusLine arrays
 * @return TRUE - if the program worked without bugs
 * @return FALSE - if the program failed to work as expected
 */

void test_by_distance (BusLine *start_sorted, BusLine *end_sorted);
/**
 * This function applies a test to check if the array is sorted by distance
 */

void test_is_equal_dis (BusLine *start_sorted, BusLine *end_sorted,
                        BusLine *start_original, BusLine *end_original);
/**
 * This function applies a test to check if the array has the same items
 * after it was sorted by distance
 */

void test_by_duration (BusLine *start_sorted, BusLine *end_sorted);
/**
 * This function applies a test to check if the array is sorted by duration
 */

void test_is_equal_dur (BusLine *start_sorted, BusLine *end_sorted,
                        BusLine *start_original, BusLine *end_original);
/**
 * This function applies a test to check if the array has the same items
 * after it was sorted by duration
 */

void create_copies_for_test (BusLine *copy_dis, BusLine *copy_dur,
                             BusLine *original_arr, int num_lines);
/**
 * This Function gets memory allocations for 2 BusLines array and copy the
 * data in the original arr to copy_dis and copy
 * @param copy_dis - Pointer to a memory allocation for the first copy of a
 * BusLine array, this array will be sorted by distance
 * @param copy_dur - Pointer to a memory allocation for the second copy of a
 * BusLine array, this array will be sorted by duration
 * @param original_arr - Pointer to the original BusLine array - isn't changed
 * through the program
 * @param num_lines - An int that represent the number of lines in the
 * 3 BusLine arrays
 */

bool allocation_success (BusLine *arr);
/**
 * This function check if the memory allocation was successful
 * @param arr - A size of an array of structs
 * @return FALSE - if the memory allocation wasn't successful
 * @return TRUE - if the memory allocation was successful
 */

int main (int argc, char *argv[])
{
  if (argc != ARG2 || !valid_args (argv[1]))
  {
    printf (ARGS_ERROR_MSG, BUBBLE, QUICK, TEST);
    return EXIT_FAILURE;
  }
  int num_lines = number_of_lines ();
  BusLine *arr = malloc (sizeof (BusLine) * num_lines);
  if (!allocation_success (arr))
  {
    return EXIT_FAILURE;
  }
  add_busline (arr, num_lines);
  if (!process_command (arr, argv[1], num_lines))
  {
    return EXIT_FAILURE;
  }
  free (arr);
  arr = NULL;
  return EXIT_SUCCESS;
}

bool process_command (BusLine *arr, char arg[], int num_lines)
{
  if (!strcmp (arg, BUBBLE))
  {
    bubble_sort (arr, arr + num_lines);
    print_array (num_lines, arr);
  }
  else if (!strcmp (arg, QUICK))
  {
    quick_sort (arr, arr + num_lines);
    print_array (num_lines, arr);
  }
  else
  {
    if (!testing_cases (num_lines, arr))
    {
      return false;
    }
  }
  return true;
}

bool testing_cases (int num_lines, BusLine *arr)
{
  BusLine *copy_dis = malloc (sizeof (BusLine) * num_lines);
  if (!allocation_success (copy_dis))
  {
    return false;
  }
  BusLine *copy_dur = malloc (sizeof (BusLine) * num_lines);
  if (!allocation_success (copy_dur))
  {
    return false;
  }
  create_copies_for_test (copy_dis, copy_dur, arr, num_lines);
  run_tests (arr,
             arr + num_lines, copy_dis,
             copy_dis + num_lines, copy_dur,
             copy_dur + num_lines);
  free (copy_dis);
  free (copy_dur);
  return true;
}

void create_copies_for_test (BusLine *copy_dis, BusLine *copy_dur,
                             BusLine *original_arr, int num_lines)
{
  memcpy (copy_dis, original_arr, (sizeof (BusLine) * num_lines));
  if (copy_dis == NULL)
  {
    free (copy_dis);
    copy_dis = NULL;
  }
  memcpy (copy_dur, original_arr, (sizeof (BusLine) * num_lines));
  if (copy_dur == NULL)
  {
    free (copy_dur);
    copy_dur = NULL;
  }
}

void run_tests (BusLine *start_original, BusLine *end_original,
                BusLine *dis_start, BusLine *dis_end, BusLine
                *dur_start, BusLine *dur_end)
{
  test_by_distance (dis_start, dis_end);
  test_is_equal_dis (dis_start, dis_end,
                     start_original, end_original);
  test_by_duration (dur_start, dur_end);
  test_is_equal_dur (dur_start, dur_end,
                     start_original, end_original);
}
void test_by_distance (BusLine *start_sorted, BusLine *end_sorted)
{
  if (is_sorted_by_distance (start_sorted, end_sorted))
  {
    printf (TEST_1_PASSED_MSG, TEST1);
  }
  else
  {
    printf (TEST_1_FAILED_MSG, TEST1);
  }
}

void test_is_equal_dis (BusLine *start_sorted, BusLine *end_sorted,
                        BusLine *start_original, BusLine *end_original)
{
  if (is_equal (start_sorted, end_sorted, start_original, end_original))
  {
    printf (TEST_2_PASSED_MSG, TEST2);
  }
  else
  {
    printf (TEST_2_FAILED_MSG, TEST2);
  }
}

void test_by_duration (BusLine *start_sorted, BusLine *end_sorted)
{
  if (is_sorted_by_duration (start_sorted, end_sorted))
  {
    printf (TEST_3_PASSED_MSG, TEST3);
  }
  else
  {
    printf (TEST_3_FAILED_MSG, TEST3);
  }
}

void test_is_equal_dur (BusLine *start_sorted, BusLine *end_sorted,
                        BusLine *start_original, BusLine *end_original)
{
  if (is_equal (start_sorted, end_sorted, start_original, end_original))
  {
    printf (TEST_4_PASSED_MSG, TEST4);
  }
  else
  {
    printf (TEST_4_FAILED_MSG, TEST4);
  }
}

int number_of_lines ()
{
  int num_lines = 0;
  char input_lines[BUFFER_LENGTH];
  while (num_lines <= 0)
  {
    printf (NUM_LINES_INPUT_MSG);
    fgets (input_lines, BUFFER_LENGTH, stdin);
    sscanf (input_lines, "%d", &num_lines);
    if (num_lines <= 0)
    {
      printf (ERROR_NUM_LINES_MSG);
    }
  }
  return num_lines;
}

bool valid_args (char argument[])
{
  if ((strcmp (argument, BUBBLE) != 0) && (strcmp (argument, QUICK) != 0)
      && (strcmp (argument, TEST) != 0))
  {
    return false;
  }
  return true;
}

void add_busline (BusLine *arr, int num_lines)
{
  int counter = 0;
  while (counter != num_lines)
  {
    int line_number, distance, duration;
    char input[INPUT_BUFFER];
    printf (LINE_INFO_MSG);
    fgets (input, INPUT_BUFFER, stdin);
    int res = sscanf (input, "%d,%d,%d", &line_number,
                      &distance, &duration);
    if (res == NUM_OF_ARGUMENTS
        && valid_input_value (line_number, distance, duration))
    {
      BusLine *ptr = &arr[counter];
      ptr->line_number = line_number;
      ptr->distance = distance;
      ptr->duration = duration;
      counter++;
    }
  }
}

bool valid_input_value (int line_number, int distance, int duration)
{
  if (duration < MIN_DURA || duration > MAX_DURA)
  {
    printf (ERROR_DURATION_RANGE_MSG,
            MIN_DURA, MAX_DURA);
    return false;
  }

  else if (distance < MIN_DIST || distance > MAX_DIST)
  {
    printf (DISTANCE_ERROR_MSG, MIN_DIST, MAX_DIST);
    return false;
  }
  else if (line_number < MIN_LINES || line_number > MAX_LINES)
  {
    printf (ERROR_LINE_NUMBER_RANGE_MSG, MIN_LINES, MAX_LINES);
    return false;
  }
  return true;
}

void print_array (int num_lines, BusLine *start)
{
  for (int j = 0; j < num_lines; j++)
  {
    printf ("%d,%d,%d\n", start[j].line_number, start[j].distance,
            start[j].duration);
  }
}

bool allocation_success (BusLine *arr)
{
  if (arr == NULL)
  {
    free (arr);
    arr = NULL;
    return false;
  }
  return true;
}
