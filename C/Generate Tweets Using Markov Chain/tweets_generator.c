#include "markov_chain.h"
#include "linked_list.h"


/***************************/
/** DEFINES FOR TWEETS GEN */
/***************************/

#define SEED 1
#define TWEETS_TO_PRINT 2
#define PATH 3
#define WORDS_TO_READ 4
#define MIN_ARGS 4
#define MAX_ARGS 5
#define NUM_BASE 10
#define MAX_SIZE_SENTENCE 20
#define INPUT_BUFFER 1001
#define NEW_LINE "\n"
#define STR_WITH_SPACE "%s "
#define STR_INDICATOR "%s"
#define DOT '.'
#define SPACE " "
#define TWEET_MSG "Tweet %d: "
#define READ_MODE "r"
#define ERROR_OPEN_FILE_MSG "Error: Can't access the tweets file\n"
#define ERROR_WRONG_ARGC_MSG "USAGE: Wrong number of arguments enter 3 or 4 \
arguments\n"

/***************************/
/** FUNCTION DESCRIPTION   */
/***************************/

/**
 * check if the word is the last word in a sentence (ends with dot)
 * @param data holds the data of a a string
 * @return 1) true - if the string ends with dot
 *         2) false - if the string doesn't ends with a dot
 */
static bool is_last (void *data);

/**
 * print the word in data
 * @param data A string that holds the data of a word
 */
static void print_func (void *data);

/**
 * free the data in the param data_ptr
 * @param data_ptr - holds the data of a cell
 */
static void free_data (void *data_ptr);

/**
 * dynamically allocate the string in data_ptr
 * @param data_ptr - holds the data to needs to be dynamically allocated
 * @return the new dynamically allocated data
 */
static void *copy_func (void *data_ptr);

/**
 * compare the strings in data 1 and data 2
 * @param data1 holds data of a string
 * @param data2 holds data of a string
 * @return 1) zero - if the strings are has the same number
 *         2) positive number - if the first non matching character in data 1
 *         is greater (in ASCII) than that of data 2
 *         3) negative number - if the first non matching character in data 1
 *         is lower (in ASCII) than that of data 2
 */
static int comp_func (void *data1, void *data2);

/** check if the user gave valid number of arguments, and a valid path to the
 * tweets file
 * @param argc Number of arguments given by the user
 * @param argv Parameters given by the user
 * @return 1) false - wrong number of arguments
 *         2) true - valid number of arguments
 */
static bool check_arguments_validation (int argc, char *argv[]);

/**
 * allocate memory for markov chain and linked list and initialize them
 * @param markov_chain a chain that holds the database
 * @return 1) true - if the allocation succeeded
 *         2) false - if the allocation failed
 */
static bool create_markov_chain (MarkovChain **markov_chain);

/**
 * @param markov_chain a chain that holds the database
 * @param corpus_path a path to the tweets file
 * @param words_to_read number of roads to read from
 * @return 1) true - if filling the markov chain succeeded
 *         2) false - if filling the markov chain failed (failed to open file
 *                      / dynamically allocated memory failed)
 */
static bool
open_file_and_fill_mc (MarkovChain *markov_chain, char *corpus_path,
                       int words_to_read);

/**
 * fill the markov chain with nodes if the nodes, if the node already in the
 * database don't append it
 * @param markov_chain a chain that holds the database
 * @param token a word that needs to be add to the database
 * @param cur_node the markov node that was added to database
 * @return 1) true - if filling the markov chain succeeded
 *         2) false - memory allocation failed
 */
static bool
add_node_to_markov_chain (MarkovChain *markov_chain, void *token,
                          Node **cur_node);

/**
 * cast parameters given by the user from string to int or unsigned int
 * @param argc number of arguments given by the user
 * @param argv an array of arguments given by the user
 * @param num_of_tweets string of numbers of tweets to print
 * @param words_to_read string of number of words to read from file path
 */
static void
recast_args_and_set_seed (int argc, char *argv[], int *num_of_tweets, int
*words_to_read);

/**
 * create a sequence using the database in markov chain and prints it
 * @param num_of_tweets number of tweets to generate and print
 * @param markov_chain a chain that holds the database
 */
static void
create_and_print_sequence (int num_of_tweets, MarkovChain *markov_chain);

/**
 *
 * @param fp file pointer to the file that was opened
 * @param words_to_read number of words to read from the file
 * @param markov_chain a chain that holds the database
 * @return 1) true - if the database filled successfully
 *         2) false - if dynamically allocated memory failed
 */
static int
fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);

/**
 * add the markov node cur_node to the counter of the markov node prev node
 * @param prev_node markov node that hold the data of the previous node
 * @param cur_node markov node that hold the data of the current node
 * @param markov_chain a chain that holds the database
 * @return 1) true - if the database filled successfully
 *         2) false - if dynamically allocated memory failed
 */
static bool
add_nnc_to_counter_list (Node *prev_node, Node *cur_node,
                         MarkovChain *markov_chain);

/**
 * this program gets a text file, read words from the text file
 * and generate sequences from the text file
 * @param argc number of arguments given by the user
 * @param argv 1) seed
 *             2) words to read
 *
 * @return 1) EXIT_SUCCESS - program run successfully
 *         2) EXIT_FAILURE - The program failed to run successfully
 */
int main (int argc, char *argv[])
{
  if (!check_arguments_validation (argc, argv))
  {
    return EXIT_FAILURE;
  }
  int num_of_tweets = 0, words_to_read = 0;
  MarkovChain *markov_chain = NULL;
  if (!create_markov_chain (&markov_chain))
  {
    return EXIT_FAILURE; // allocation failure
  }
  recast_args_and_set_seed (argc, argv, &num_of_tweets, &words_to_read);
  if (!open_file_and_fill_mc (markov_chain, argv[PATH], words_to_read))
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE; // allocation failure
  }
  create_and_print_sequence (num_of_tweets, markov_chain);
  free_markov_chain (&markov_chain);
  return EXIT_SUCCESS;
}

//markov chain methods
static void print_func (void *data)
{
  char *data_string = (char *) data;
  if (is_last (data_string))
  {
    printf (STR_INDICATOR, data_string);
  }
  else
  {
    printf (STR_WITH_SPACE, data_string);
  }
}

static bool is_last (void *data)
{
  char *new_data = (char *) (data);
  size_t length = strlen (new_data) - 1;
  if (new_data[length] == DOT)
  {
    return true;
  }
  return false;
}

static void *copy_func (void *data_ptr)
{
  char *tweet = (char *) data_ptr;
  tweet[strcspn (tweet, NEW_LINE)] = 0;
  size_t length = strlen (tweet) + 1;
  char *data = malloc (length + 1);
  strcpy (data, tweet);
  if (data == NULL)
  {
    return NULL;
  }
  return data;
}

static int comp_func (void *data1, void *data2)
{
  char *word1 = (char *) data1;
  char *word2 = (char *) data2;
  return strcmp (word1, word2);
}

static void free_data (void *data_ptr)
{
  free (data_ptr);
}

static bool check_arguments_validation (int argc, char *argv[])
{
  if (argc != MIN_ARGS && argc != MAX_ARGS)
  {
    printf (ERROR_WRONG_ARGC_MSG);
    return false;
  }
  FILE *file_ptr = fopen (argv[PATH], READ_MODE);
  if (file_ptr == NULL)
  {
    printf (ERROR_OPEN_FILE_MSG);
    return false;
  }
  else
  {
    fclose (file_ptr);
  }
  return true;
}

static bool create_markov_chain (MarkovChain **markov_chain)
{
  *markov_chain = (MarkovChain *) malloc (sizeof (MarkovChain));
  if ((*markov_chain) == NULL)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return false; // allocation failure
  }
  LinkedList *linked_list = (LinkedList *) malloc (sizeof (LinkedList));
  if (linked_list == NULL)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    free (*markov_chain);
    *markov_chain = NULL; // allocation failure
    return false;
  }
  *linked_list = (LinkedList) {NULL, NULL, 0};
  **markov_chain = (MarkovChain) {linked_list, print_func, comp_func,
                                  free_data, copy_func, is_last};
  return true;
}

static void
recast_args_and_set_seed (int argc, char *argv[], int *num_of_tweets, int
*words_to_read)
{
  unsigned int seed = (unsigned int) strtol (argv[SEED], NULL, NUM_BASE);
  srand (seed);
  int tweets = (int)strtol (argv[TWEETS_TO_PRINT], NULL, NUM_BASE);
  *num_of_tweets = (int) tweets;
  if (argc == MAX_ARGS)
  {
    int word_read = (int) strtol (argv[WORDS_TO_READ], NULL, NUM_BASE);
    *words_to_read = (int) word_read;
  }
  else
  {
    *words_to_read = -1;
  }
}

static bool
open_file_and_fill_mc (MarkovChain *markov_chain, char *corpus_path,
                       int words_to_read)
{
  FILE *fp = fopen (corpus_path, READ_MODE);
  if (fp == NULL) // check if file failed to open
  {
    free_markov_chain (&markov_chain);
    return false; // allocation failure
  }
  int fill_res = fill_database (fp, words_to_read, markov_chain);
  fclose (fp);
  if (fill_res)
  {
    free_markov_chain (&markov_chain);
    return false; // allocation failure
  }
  return true;
}

static bool
add_node_to_markov_chain (MarkovChain *markov_chain, void *token,
                          Node **cur_node)
{
  char* new_token = (char*) token;
  new_token[strcspn (new_token,NEW_LINE)] = 0;
  *cur_node = add_to_database (markov_chain, new_token);
  if (*cur_node == NULL)
  {
    return false; // allocation failure
  }
  return true;
}

static bool
add_nnc_to_counter_list (Node *prev_node, Node *cur_node,
                         MarkovChain *markov_chain)
{
  if (prev_node && !(markov_chain->is_last (prev_node->data->data)))
  {
    if (!add_node_to_counter_list (prev_node->data,
                                   cur_node->data, markov_chain))
    {
      return false; // allocation failure
    }
  }
  return true;
}

static int
fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char tweet[INPUT_BUFFER]; //1000 words in tweet + '\0'
  char *token = NULL;
  Node *prev_node = NULL, *cur_node = NULL;
  while (fgets (tweet, INPUT_BUFFER, fp) && words_to_read)
  {
    token = strtok (tweet, SPACE);
    while (token && words_to_read) //read until the tweet is over
    {
      words_to_read--;
      if (!add_node_to_markov_chain (markov_chain, token, &cur_node))
      {
        return 1; // allocation failure
      }
      if (!add_nnc_to_counter_list (prev_node, cur_node, markov_chain))
      {
        return 1; // allocation failure
      }
      prev_node = cur_node; // pointer to previous node to add to counter list
      token = strtok (NULL, SPACE);
    }
  }
  return 0;
}

static void
create_and_print_sequence (int num_of_tweets, MarkovChain *markov_chain)
{
  for (int i = 0; i < num_of_tweets; i++)
  {
    printf (TWEET_MSG, (i + 1));
    generate_random_sequence (markov_chain, NULL, MAX_SIZE_SENTENCE);
    printf (NEW_LINE);
  }
}