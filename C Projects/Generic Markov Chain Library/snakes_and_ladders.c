#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

/***************************/
/**   DEFINES FOR SNAKES   */
/***************************/

#define SEED 1
#define NUM_OF_ROADS 2
#define ARGS_NUM 3
#define NUM_BASE 10
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60
#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define LAST_CELL 100
#define RANDOM_WALK_STR "Random Walk %d: "
#define SNAKE_TO_STR "-snake to %d "
#define LADDER_TO "-ladder to %d "
#define CELL_BOX_MSG "[%d]"
#define ARROW_SIGN "-> "
#define STR_INDICATOR "%s"
#define NEW_LINE "\n"
#define SPACE " "
#define ERROR_WRONG_ARGC_MSG "USAGE: Wrong number of arguments: Enter only 2 \
arguments\n"

/***************************/
/** FUNCTION DESCRIPTION   */
/***************************/

/**
 * check if the cell is the last is the last cell in the game (100)
 * @param data holds the data of a cell
 * @return 1) true - the data holds the last cell data
 *         2) false - the data doesn't hold the last cell data
 */
static bool is_last (void *data);

/**
 * print the cell data and another data (ladder or snake)
 * according to the gameplay
 * @param data A cell that holds the data of a cell
 */
static void print_func (void *data);

/**
 * free the data in the param data_ptr
 * @param data_ptr - holds the data of a cell
 */
static void free_data (void *data_ptr);

/**
 * dynamically allocate the cell in data_ptr
 * @param data_ptr - holds the data to needs to be dynamically allocated
 * @return the new dynamically allocated data
 */
static void *copy_func (void *data_ptr);

/**
 * compare the number of 2 cells
 * @param data1 holds data of a cell
 * @param data2 holds data of a cell
 * @return 1) zero - if the cells has the same number
 *         2) positive number - if cell 1 (data1) has higher number than
 *         cell 2 (data 2)
 *         3) negative number - if cell 1 (data1)has lower number than
 *         cell 2 (data 2)
 */
static int comp_func (void *data1, void *data2);

/** check the arguments given by the user
 * @param argc Number of arguments given by the user
 * @return 1) false - wrong number of arguments
 *         2) true - valid number of arguments
 */
static bool check_arguments_validation (int argc);

/**
 * allocate memory for markov chain and linked list and initialize them
 * @param markov_chain a chain that holds the database
 * @return 1) true - if the allocation succeeded
 *         2) false - if the allocation failed
 */
static bool create_markov_chain (MarkovChain **markov_chain);

/**
 * 1) cast the parameters given by the user from string to int.
 * 2) activate seed.
 * @param parameters holds the parameters given by the user.
 * @return An int that holds the number of roads to print
 */
static unsigned int recast_args_and_set_seed (char *parameters[]);

/**
 * print roads according to the number in num_of_roads
 * @param num_of_roads hold the number of roads to print
 * @param markov_chain a chain that holds the database
 */
static void
create_and_print_roads (unsigned int num_of_roads, MarkovChain *markov_chain);

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8, 30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell
{
  int number; // Cell number 1-100
  int ladder_to;  // ladder_to represents the jump of the ladder in case there
  // is one from this square
  int snake_to;  // snake_to represents the jump of the snake in case there
  // is one from this square
  //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/**
 * Error handler function to free memory allocated
 * @param error_msg a massage that
 * @param database a markov chain that holds the data base
 * @return EXIT_FAILURE the function is called when program failed so
 *         the program failed to operate correctly
 */
static int handle_error (char *error_msg, MarkovChain **database)
{
  printf (STR_INDICATOR, error_msg);
  if (database != NULL)
  {
    free_markov_chain (database);
  }
  return EXIT_FAILURE;
}

/**
 * allocate memory for cells in the game board from numbers 1 to 100
 * @param cells a cell in the game board
 * @return 1) EXIT_SUCCESS - allocate memory operation was successful
 *         2) EXIT_FAILURE - allocate memory operation failed
 */
static int create_board (Cell *cells[BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    cells[i] = malloc (sizeof (Cell));
    if (cells[i] == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free (cells[j]);
      }
      handle_error (ALLOCATION_ERROR_MASSAGE, NULL);
      return EXIT_FAILURE;
    }
    *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
  }

  for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
  {
    int from = transitions[i][0];
    int to = transitions[i][1];
    if (from < to)
    {
      cells[from - 1]->ladder_to = to;
    }
    else
    {
      cells[from - 1]->snake_to = to;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * fills the database
 * @param markov_chain database to fill the data in it
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database (MarkovChain *markov_chain)
{
  Cell *cells[BOARD_SIZE];
  if (create_board (cells) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  MarkovNode *from_node = NULL, *to_node = NULL;
  size_t index_to;
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    Node* cur_node = add_to_database (markov_chain, cells[i]);
    if (cur_node == NULL)
    {
      return EXIT_FAILURE; // allocation failure
    }
  }

  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    from_node = get_node_from_database (markov_chain, cells[i])->data;

    if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
    {
      index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
      to_node = get_node_from_database (markov_chain, cells[index_to])
          ->data;
      if (!add_node_to_counter_list (from_node, to_node, markov_chain))
      {
        return EXIT_FAILURE;
      }
    }
    else
    {
      for (int j = 1; j <= DICE_MAX; j++)
      {
        index_to = ((Cell *) (from_node->data))->number + j - 1;
        if (index_to >= BOARD_SIZE)
        {
          break;
        }
        to_node = get_node_from_database (markov_chain, cells[index_to])
            ->data;
        if (!add_node_to_counter_list (from_node, to_node, markov_chain))
        {
          return EXIT_FAILURE;
        }
      }
    }
  }
  // free temp arr
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    free (cells[i]);
  }
  return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main (int argc, char *argv[])
{
  if (!check_arguments_validation (argc))
  {
    return EXIT_FAILURE; // EXIT PROGRAM - wrong number of args given
  }
  MarkovChain *markov_chain = NULL;
  if (!create_markov_chain (&markov_chain))
  {
    return EXIT_FAILURE; // allocation failure
  }
  unsigned int num_of_roads = recast_args_and_set_seed (argv);
  if (fill_database (markov_chain))
  {
    handle_error (ALLOCATION_ERROR_MASSAGE, &markov_chain);
    return EXIT_FAILURE; // allocation failure
  }
  create_and_print_roads (num_of_roads, markov_chain);
  free_markov_chain (&markov_chain);
  return EXIT_SUCCESS;
}

static bool check_arguments_validation (int argc)
{
  if (argc != ARGS_NUM)
  {
    printf (STR_INDICATOR, ERROR_WRONG_ARGC_MSG);
    return false;
  }
  return true;
}

static bool create_markov_chain (MarkovChain **markov_chain)
{
  *markov_chain = (MarkovChain *) malloc (sizeof (MarkovChain));
  if ((*markov_chain) == NULL)
  {
    printf (STR_INDICATOR, ALLOCATION_ERROR_MASSAGE);
    return false; // allocation failure
  }
  LinkedList *linked_list = (LinkedList *) malloc (sizeof (LinkedList));
  if (linked_list == NULL)
  {
    printf (STR_INDICATOR, ALLOCATION_ERROR_MASSAGE);
    free (*markov_chain);
    *markov_chain = NULL; // allocation failure
    return false;
  }
  *linked_list = (LinkedList) {NULL, NULL, 0};
  **markov_chain = (MarkovChain) {linked_list, print_func, comp_func,
                                  free_data, copy_func, is_last};
  return true;
}

static unsigned int recast_args_and_set_seed (char *parameters[])
{
  unsigned int seed = (unsigned int) strtol (parameters[SEED],
                                             NULL, NUM_BASE);
  srand (seed);
  unsigned int num_of_roads = (unsigned int) strtol (parameters[NUM_OF_ROADS],
                                                     NULL, NUM_BASE);
  return num_of_roads;
}

static void
create_and_print_roads (unsigned int num_of_roads, MarkovChain *markov_chain)
{
  for (unsigned int i = 0; i < num_of_roads; i++)
  {
    printf (RANDOM_WALK_STR, (i + 1));
    MarkovNode *first_node = markov_chain->database->first->data;
    generate_random_sequence (markov_chain, first_node, MAX_GENERATION_LENGTH);
    printf (NEW_LINE);
  }
}

static void print_func (void *data)
{
  Cell *cell = (Cell *) data;
  printf (CELL_BOX_MSG, cell->number);
  if (cell->snake_to != EMPTY)
  {
    printf (SNAKE_TO_STR, cell->snake_to);
  }
  else if (cell->ladder_to != EMPTY)
  {
    printf (LADDER_TO, cell->ladder_to);
  }
  else if (!is_last (cell))
  {
    printf (SPACE);
  }
  if(!is_last (cell))
  {
    printf (ARROW_SIGN);
  }
}

static bool is_last (void *data)
{
  Cell *cell = (Cell *) data;
  if (cell->number == LAST_CELL)
  {
    return true;
  }
  return false;
}

static void *copy_func (void *data_ptr)
{
  Cell *new_data = (Cell *) malloc (sizeof (Cell));
  if (new_data == NULL)
  {
    return NULL;
  }
  Cell *data = (Cell *) data_ptr;
  *new_data = (Cell) {data->number, data->ladder_to, data->snake_to};
  return new_data;
}

static int comp_func (void *data1, void *data2)
{
  Cell *cell1 = data1;
  Cell *cell2 = data2;
  return cell1->number - cell2->number;
}

static void free_data (void *data_ptr)
{
  free (data_ptr);
}
