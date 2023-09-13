#include "markov_chain.h"

/** description of the functions in this file are in markov_chain.h file */

Node *add_to_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *node_exist = get_node_from_database (markov_chain, data_ptr);
  if (node_exist)
  {
    return node_exist;
  }
  MarkovNode *markov_node = (MarkovNode *) malloc (sizeof (MarkovNode));
  if (markov_node == NULL)
  {
    return false; // allocation failure
  }
  void *data = markov_chain->copy_func (data_ptr);
  if (data == NULL)
  {
    free(markov_node); // free - not yet in markov chain
    return false;
  }
  *markov_node = (MarkovNode) {data, 0, 0, NULL};
  if (add (markov_chain->database, markov_node))
  {
    free(markov_node); // free - not yet in markov chain
    free(data); // free - not yet in markov chain
    return NULL; // allocation failure
  }
  return markov_chain->database->last;
}

Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *head = markov_chain->database->first;
  while (head != NULL && markov_chain->comp_func (data_ptr, head->data->data))
  {
    head = head->next;
  }
  return head;
}

bool
add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node,
                          MarkovChain *markov_chain)
{
  if (in_counter_list (first_node, second_node, markov_chain)) // in ctr lst
  {
    return true;
  }
  if (first_node->size == 0)
  {
    if (!create_new_counter_list (first_node))
    {
      return false; // allocation failure
    }
  }
  else
  {
    if (!extend_counter_list (first_node))
    {
      return false; // allocation failure
    }
  }
  if (!allocate_nnc_to_counter_list (first_node, second_node))
  {
    return false; // allocation failure
  }
  return true;
}

bool
in_counter_list (MarkovNode *first_node, MarkovNode *second_node,
                 MarkovChain *markov_chain)
{
  for (int i = 0; i < first_node->size; i++) //in ctr lst
  {
    NextNodeCounter *node_counter = first_node->counter_list[i];
    void *data1 = node_counter->markov_node->data;
    void *data2 = second_node->data;
    if (!markov_chain->comp_func (data1, data2))
    {
      node_counter->freq++;
      first_node->sum_freq++;
      return true;
    }
  }
  return false;
}

bool create_new_counter_list (MarkovNode *first_node)
{
  NextNodeCounter **arr = (NextNodeCounter **) malloc
      (sizeof (NextNodeCounter *));
  if (arr == NULL)
  {
    return false; // allocation failure
  }
  first_node->counter_list = arr;
  return true;
}

bool extend_counter_list (MarkovNode *first_node)
{
  int size = (first_node->size + 1);
  NextNodeCounter **extension = realloc (first_node->counter_list,
                                         (sizeof (NextNodeCounter *)) * size);
  if (extension == NULL)
  {
    return false; // allocation failure
  }
  first_node->counter_list = extension;
  return true;
}

bool allocate_nnc_to_counter_list (MarkovNode *first_node, MarkovNode *
second_node)
{
  NextNodeCounter *node_counter = (NextNodeCounter *)
      malloc (sizeof (NextNodeCounter));
  if (node_counter == NULL)
  {
    if (first_node->size == 0)
    {
      free(first_node->counter_list); // edge case - allocated empty cl
    }
    return false; // allocation failure
  }
  int size = first_node->size;
  *node_counter = (NextNodeCounter) {second_node, 1};
  first_node->counter_list[size] = node_counter;
  first_node->sum_freq++;
  first_node->size++;
  return true;
}

int get_random_number (int max_number)
{
  return rand() % max_number;
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  Node *head = markov_chain->database->first;
  bool roll_word_with_dot = true;
  while (roll_word_with_dot)
  {
    Node *copy_head = head;
    int random_num = get_random_number (markov_chain->database->size);
    for (int i = 0; i < random_num; i++)
    {
      copy_head = copy_head->next;
    }
    if (!markov_chain->is_last (copy_head->data->data))
    {
      head = copy_head;
      roll_word_with_dot = false;
    }
  }
  return head->data;
}

MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  int sum_freq = state_struct_ptr->sum_freq;
  int random_num = (get_random_number (sum_freq) + 1), i = 0;
  int sum = state_struct_ptr->counter_list[0]->freq;
  while (sum < random_num)
  {
    i++;
    sum += state_struct_ptr->counter_list[i]->freq;
  }
  return state_struct_ptr->counter_list[i]->markov_node;
}

void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  if (!first_node)
  {
    first_node = get_first_random_node (markov_chain);
  }
  max_length--;
  while (max_length != 0 && !(markov_chain->is_last (first_node->data)))
  {
    markov_chain->print_func (first_node->data);
    first_node = get_next_random_node (first_node);
    max_length--;
  }
  markov_chain->print_func (first_node->data);
}

void free_markov_chain (MarkovChain **ptr_chain)
{
  Node *head = (*ptr_chain)->database->first;
  int size = (*ptr_chain)->database->size;
  for (int i = 0; i < size; i++)
  {
    MarkovNode *markov_node = head->data;
    int j = 0;
    for (; j < markov_node->size; j++)
    {
      free (markov_node->counter_list[j]); // free NextNodeCounter
    }
    (*ptr_chain)->free_data (markov_node->data); // free the data in MarkovNode
    if (j != 0)
    {
      free (markov_node->counter_list); // free NNC array
    }
    free (markov_node); // free Markov Node
    Node *next = head->next;
    free (head); // free Node
    head = next;
  }
  free ((*ptr_chain)->database); // free LinkedList
  free (*ptr_chain); // free Markov Chain
  *ptr_chain = NULL;
}


