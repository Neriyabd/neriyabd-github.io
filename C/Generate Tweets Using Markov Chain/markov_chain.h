#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool
#include <string.h>

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate \
new memory\n"

/***************************/
/**        STRUCTS         */
/***************************/

/**
 * struct that represent next element in counter list
 */
typedef struct NextNodeCounter
{
  struct MarkovNode *markov_node;
  int freq;
} NextNodeCounter;

/**
 * struct that represents a markov node that contain the data to generate from
 */
typedef struct MarkovNode
{
  void *data;
  int size;
  int sum_freq;
  struct NextNodeCounter **counter_list;
} MarkovNode;

/**
 * struct that contain the database for the program and methods for generic
 * programming
 */
/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain
{
  LinkedList *database;

  // pointer to a func that receives data from a generic type and prints it
  // returns void.
  void (*print_func) (void *data);

  // pointer to a func that gets 2 pointers of generic data type(same one)
  // and compare between them */
  // returns: - a positive value if the first is bigger
  //          - a negative value if the second is bigger
  //          - 0 if equal
  int (*comp_func) (void *data1, void *data2);

  // a pointer to a function that gets a pointer of generic data type and
  // frees it.
  // returns void.
  void (*free_data) (void *data_ptr);

  // a pointer to a function that  gets a pointer of generic data type and
  // returns a newly allocated copy of it
  // returns a generic pointer.
  void *(*copy_func) (void *data_ptr);

  //  a pointer to function that gets a pointer of generic data type and
  //  returns:
  //      - true if it's the last state.
  //      - false otherwise.
  bool (*is_last) (void *data);
} MarkovChain;

/***************************/
/** FUNCTION DESCRIPTION   */
/***************************/

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode *get_first_random_node (MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with, if NULL- choose a random
 * markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_markov_chain (MarkovChain **markov_chain);

/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_counter_list (MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it
 * in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return it's markov_node. Otherwise, create new
 * markov_node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database
 */
Node *add_to_database (MarkovChain *markov_chain, void *data_ptr);

/**
 * allocate counter list to the first node (a markov node)
 * @param first_node
 * @return 1) true - if the allocation succeeded
 *         2) false - if the allocation failed
 */
bool create_new_counter_list (MarkovNode *first_node);

/**
 * allocate an next node counter add the data of second markov node to next
 * node counter and append it to the counter list of the first markov node
 * @param first_node markov node to create its counter list
 * @param second_node markov node to add to first node counter list
 * @return 1) true - if the allocation succeeded
 *         2) false - if the allocation failed
 */
bool allocate_nnc_to_counter_list (MarkovNode *first_node, MarkovNode
*second_node);

/**
 * a new markov node needs to be added to the counter list,
 * extend the counter list dynamically memory allocated by 1
 * @param first_node a markov node to extend it's counter list
 * @return 1) true - if the allocation succeeded
 *         2) false - if the allocation failed
 */
bool extend_counter_list (MarkovNode *first_node);

/**
 * check if the second markov node is already in the counter of the first
 * markov node
 * @param first_node markov node to check on its counter list
 * @param second_node markov node to check if its already in first node
 * counter list
 * @param markov_chain the chain that hold that database
 * @return 1) true - if second markov node is already in the counter list
 *         2) false - if second markov node isn't in the counter list
 */
bool
in_counter_list (MarkovNode *first_node, MarkovNode *second_node,
                 MarkovChain *markov_chain);
#endif /* markovChain_h */
