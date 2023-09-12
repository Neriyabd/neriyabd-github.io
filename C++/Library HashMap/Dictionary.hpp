#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "HashMap.hpp"
#define INVALID_KEY_ERROR_MSG "Invalid Key, the key doesn't exist in hash map"

typedef HashMap<std::string, std::string> str_hash_map;

/**
 * class that override exception invalid argument into a unique exception
 */
class InvalidKey : public std::invalid_argument
{
 public:
  InvalidKey () : std::invalid_argument (INVALID_KEY_ERROR_MSG)
  {};
  explicit InvalidKey (const std::string &str_key)
      : std::invalid_argument (str_key)
  {};

};

/**
 * Dictionary class that derive hash map as data structures
 */
class Dictionary : public str_hash_map
{
 public:
  using HashMap::HashMap;
  /**
   * erase the string if the key string is in the hash map
   * if key is not in the hash map raises exception
   * @param str_key - a string's key
   * @return true of key was deleted from the map
   */
  bool erase (const std::string &str_key) override;
  /**
   * get 2 iterators and insert all item from the iterator to the dictionary
   * @param begin_iter - an iterator to begin in
   * @param end_iter - an iterator to end at
   */
  template<class IteratorT>
  void update (IteratorT begin_iter, IteratorT end_iter);

};

bool Dictionary::erase (const std::string &str_key)
{
  if (HashMap::erase (str_key))
  {
    return true;
  }
  throw InvalidKey ();
}

template<class IteratorT>
void Dictionary::update (IteratorT begin_iter, IteratorT end_iter)
{
  for (auto it = begin_iter; it != end_iter; it++)
  {
    const auto &key = it->first;
    const auto &value = it->second;
    operator[] (key) = value;
  }
}

#endif //_DICTIONARY_H_
