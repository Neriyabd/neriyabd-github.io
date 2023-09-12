#ifndef _HASHMAP_HPP_
#define _HASHMAP_HPP_

#include <vector>
#include <iostream>
#include <algorithm>

#define UPPER_LOAD_FACTOR 0.75
#define LOWER_LOAD_FACTOR 0.25
#define INITIAL_CAPACITY 16
#define VECTOR_LEN_ERROR_MSG "Vectors are not in the same length"
#define OUT_OF_RANGE_ERROR_MSG "Key is not found"

template<class KeyT, class ValueT>
class HashMap
{
 public:
  class ConstIterator;
  typedef ConstIterator const_iterator;
  typedef std::pair<KeyT, ValueT> pair;
  typedef std::vector<std::pair<KeyT, ValueT>> bucket;
  typedef HashMap<KeyT, ValueT> HashMapT;
  typedef std::vector<std::pair<KeyT, ValueT>> *my_hash_map;
  typedef const std::vector<ValueT> value_vec;
  typedef const std::vector<KeyT> key_vec;

  /**
   * default constructor
   */
  HashMap ();
  /**
   * copy constructor
   * @param copy_hash_map - a hash map to copy data from
   */
  HashMap (const HashMap &copy_hash_map);
  /**
   * a constructor that get a vector of keys and values and initializes
   * the a hash map with those keys and values
   * @param keys
   * @param values
   */
  HashMap (const key_vec &keys, const value_vec &values);
  /**
   * destructor for the hash map
   */
  virtual ~HashMap ();
  /**
   * a getter for the size (number of pairs) of the hash map
   * @return an int that represents the size
   */
  int size () const;
  /**
   * a getter for the capacity of the hash map
   * @return an int that represents the capacity
   */
  int capacity () const;
  /**
   * check if the hash map is empty
   * @return true - the hash map is empty
   * @return false - the hash map is not empty
   */
  bool empty () const;
  /**
   * insert a pair of key and value to the hash map,
   * if key already exist doesn't change the key that was already in hash map
   * @param key - key to insert
   * @param value - value to insert
   * @return true - inserted the key
   * @return false - the key already exist in hash map
   */
  bool insert (const KeyT &key, const ValueT &value);
  /**
   * check if a key is in the hash map
   * @param key - a hash map key
   * @return true - if key exist in map
   * @return false - key doesn't exist in map
   */
  bool contains_key (const KeyT &key) const;
  /**
   * gets a key as parameter and return the a value attached to key
   * if key isn't found, raise exception
   * @param key - a hash map key
   * @return the value attached to key as ref
   */
  ValueT &at (const KeyT &key);
  /**
   * gets a key as parameter and return the value of the key
   * if key isn't found, raise exception
   * @return - the value attached to key as const ref
   */
  const ValueT &at (const KeyT &key) const;
  /**
   * calculate the load factor of the hash map (size / capacity) of hash map
   * @param key - a hash map key
   * @return a double of the load factor of map
   */
  double get_load_factor () const;
  /**
   * gets a key and check for the size of bucket that key is in
   * if key isn't found, raise exception
   * @param key - a hash map key
   * @return an int of the size of bucket key is in
   */
  int bucket_size (const KeyT &key) const;
  /**
   * gets a key and check for the bucket his index are in
   * if key isn't found, raise exception
   * @param key - a hash map key
   * @return an int of the bucket index key is in
   */
  int bucket_index (const KeyT &key) const;
  /**
   * gets a key as parameter, if the key exist in the hash map, erases
   * the key from the hash map
   * @return true - the key was removed
   * @return false - the key doesn't exist in hash map
   */
  virtual bool erase (const KeyT &key);
  /**
   * clear all the _buckets in the hashmap,
   * removing all the elements
   */
  void clear ();
  /**
   * assign a hash map got in parameter to this hash map
   * @param assign_map - map to assign member hash map to
   * @return a reference to this
   */
  HashMapT &operator= (const HashMapT &assign_map);
  /**
   * gets a key and returned the value that attached to key
   * @param key - a hash map's key
   * @return const reference to the value of key
   */
  ValueT &operator[] (const KeyT &key);
  /**
   * gets a key and returned the value that attached to key as reference,
   * if key doesn't exist, append new key and value
   * @param key - a hash map's key
   * @return reference to the value of key
   */
  const ValueT &operator[] (const KeyT &key) const;
  /**
   * check if 2 hash map are equal
   * @param compare_map - a hash map to compare (this) to
   * @return true - hash maps are equal
   * @return false - hash maps are unequal
   */
  bool operator== (const HashMap &compare_map) const;
  /**
   * check if 2 hash map are unequal
   * @param compare_map - a hash map to compare (this) to
   * @return true - hash maps are unequal
   * @return false - hash maps are equal
   */
  bool operator!= (const HashMap &compare_map) const;

  /**
   * begin and end for const iterator implementation
   */
  const_iterator begin () const
  { return ConstIterator (this); }
  const_iterator cbegin () const
  { return ConstIterator (this); }
  const_iterator end () const
  { return ConstIterator (this, -1, -1); }
  const_iterator cend () const
  { return ConstIterator (this, -1, -1); }

 private:
  int _capacity;
  int _size;
  ValueT _default_value;
  my_hash_map _buckets{};
  /**
   * if load factor is out of range, this function
   * find the capacity that updated capacity
   * @return an int that represent the valid capacity
   */
  int find_new_capacity ();
  /**
   * a hashing function, get a key and return the
   * index to insert it in hash map
   * @param key - hash map's key
   * @return an int from the hashing func
   */
  int hashing (const KeyT &key) const;
  /**
   * gets new capacity and initialize a new hash map according
   * to the new capacity
   * @param new_capacity - new capacity to rehash the Hashmap to
   */
  void rehashing (int new_capacity);

 public:
  /**
   * An Iterator class for HashMap
   */
  class ConstIterator
  {
   private:
    const HashMapT *_iter_ptr_map;
    int _ind_bucket;
    int _ind_pair;

   public:
    /**
     * mandatory typedef for iterator class
     */
    typedef pair value_type;
    typedef const pair &reference;
    typedef const pair *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    /**
     * initializes constructor for iterator
     * @param hash_map
     */
    explicit ConstIterator (const HashMapT *hash_map)
        : _iter_ptr_map (hash_map), _ind_bucket (0), _ind_pair (0)
    { find_next_element (); }
    /**
     *
     * @param hash_map - a pointer to the hash map
     * @param ind_bucket - the index of the bucket iterator is in
     * @param ind_pair - the index of an pair inside the bucket
     */
    ConstIterator (const HashMapT *hash_map, int ind_bucket, int ind_pair)
        : _iter_ptr_map (hash_map), _ind_bucket (ind_bucket),
          _ind_pair (ind_pair)
    {}

    /**
     * find the next element to iterate to
     */
    void find_next_element ()
    {
      for (int i = _ind_bucket; i < _iter_ptr_map->_capacity; ++i)
      {
        const bucket &bucket = _iter_ptr_map->_buckets[i];
        if (!bucket.empty ())
        {
          this->_ind_bucket = i;
          this->_ind_pair = 0;
          return;
        }
      }
      _ind_bucket = -1;
      _ind_pair = -1;
    }
    /**
     * gets the next element to iterate to
     * @return the element after the iteration
     */
    const_iterator &operator++ ()
    {
      if (_ind_pair + 1 == (int) _iter_ptr_map->_buckets[_ind_bucket].size ())
      {
        _ind_bucket++;
        find_next_element ();
      }
      else
      {
        _ind_pair++;
      }
      return *this;
    }

    /**
     * gets the next element to iterate to
     * @return the element before the iteration
     */
    const_iterator operator++ (int)
    {
      const ConstIterator it (*this);
      operator++ ();
      return it;
    }

    /**
     * @param compare_iter - check if 2 iterators are equal
     * @return true - iterators are equal
     * @return false - iterators are unequal
     */
    bool operator== (const ConstIterator &compare_iter) const
    {
      return (_ind_pair == compare_iter._ind_pair && _ind_bucket ==
                                                     compare_iter._ind_bucket
              && _iter_ptr_map == compare_iter._iter_ptr_map);
    }

    /**
     * @param compare_iter - check if 2 iterators are equal
     * @return true - iterators are unequal
     * @return false - iterators are equal
     */
    bool operator!= (const ConstIterator &compare_iter) const
    {
      return !(operator== (compare_iter));
    }

    /**
     * dereference to the pair of the iterator is currently at
     * @return a pair of key and value
     */
    reference operator* () const
    {
      return _iter_ptr_map->_buckets[_ind_bucket][_ind_pair];
    }

    /**
     * a pointer to the pair
     * @return a pointer to the pair of key and value
     */
    pointer operator-> () const
    {
      return &(operator* ());
    }
  };
};

/** function implementation for HashMap class - documentation in class */

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap ()
{
  _capacity = INITIAL_CAPACITY;
  _size = 0;
  _buckets = new bucket[INITIAL_CAPACITY];
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap (const key_vec &keys, const value_vec &values)
{
  if (keys.size () != values.size ())
  {
    throw std::length_error (VECTOR_LEN_ERROR_MSG);
  }
  _size = 0;
  _capacity = INITIAL_CAPACITY;
  _buckets = new bucket[_capacity];
  for (int i = (int) keys.size () - 1; i >= 0; --i)
  {
    if (contains_key (keys[i]))
    {
      continue;
    }
    else
    {
      insert (keys[i], values[i]);
    }
  }
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap (const HashMap &copy_hash_map)
{
  _capacity = copy_hash_map._capacity;
  _size = copy_hash_map._size;
  _buckets = new bucket[_capacity];
  const my_hash_map &other_map = copy_hash_map._buckets;
  for (int i = 0; i < _capacity; ++i)
  {
    if (!other_map[i].empty ())
    {
      bucket vec (other_map[i]);
      _buckets[i] = vec;
    }
  }
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::~HashMap ()
{
  delete[] _buckets;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::size () const
{
  return _size;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::capacity () const
{
  return _capacity;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty () const
{
  return (_size == 0);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert (const KeyT &key, const ValueT &value)
{
  if (contains_key (key)) // check if key exists
  {
    return false;
  }
  int index = hashing (key);
  bucket &vec = this->_buckets[index];
  vec.push_back ({key, value});
  _size++;
  if (UPPER_LOAD_FACTOR < get_load_factor () && _size != 0)
  {
    int new_capacity = find_new_capacity ();
    rehashing (new_capacity);
  }
  return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::contains_key (const KeyT &key) const
{
  int index = hashing (key);
  bucket &vec = this->_buckets[index];
  for (size_t i = 0; i < vec.size (); i++)
  {
    if (vec[i].first == key)
    { return true; }
  }
  return false;
}

template<class KeyT, class ValueT>
const ValueT &HashMap<KeyT, ValueT>::at (const KeyT &key) const
{
  if (contains_key (key))
  {
    int index = hashing (key);
    const bucket &my_bucket = _buckets[index];
    for (size_t i = 0; i < my_bucket.size (); i++)
    {
      const KeyT &searched_key = my_bucket[i].first;
      if (key == searched_key)
      {
        return my_bucket[i].second;
      }
    }
  }
  throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
}

template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at (const KeyT &key)
{
  if (contains_key (key))
  {
    int index = hashing (key);
    bucket &my_bucket = _buckets[index];
    for (size_t i = 0; i < my_bucket.size (); i++)
    {
      const KeyT &searched_key = my_bucket[i].first;
      if (key == searched_key)
      {
        return my_bucket[i].second;
      }
    }
  }
  throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase (const KeyT &key)
{
  if (!contains_key (key)) // if key exists
  {
    return false;
  }
  _size--; // decrease size (remove item from hashmap)
  int index = hashing (key);
  bucket &my_bucket = _buckets[index];
  pair my_pair = std::make_pair (key, at (key));
  my_bucket.erase (std::remove (my_bucket.begin (), my_bucket.end (),
                                my_pair), my_bucket.end ());
  if (get_load_factor () < LOWER_LOAD_FACTOR)
  {
    int new_capacity = find_new_capacity ();
    rehashing (new_capacity);
  }
  return true;
}

template<class KeyT, class ValueT>
double HashMap<KeyT, ValueT>::get_load_factor () const
{
  double size = _size;
  double capacity = _capacity;
  return size / capacity;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_size (const KeyT &key) const
{
  if (!contains_key (key))
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  int ind = hashing (key);
  int size_of_bucket = (int) _buckets[ind].size ();
  return size_of_bucket;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_index (const KeyT &key) const
{
  if (!(contains_key (key)))
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  int index = hashing (key);
  return index;
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear ()
{
  for (int i = 0; i < _capacity; i++)
  { _buckets[i].clear (); }
  _size = 0;
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &
HashMap<KeyT, ValueT>::operator= (const HashMapT &assign_map)
{
  if (&assign_map == this)
  { return *this; }
  delete[] _buckets;
  _capacity = assign_map._capacity, _size = assign_map._size;
  _buckets = new bucket[_capacity];
  const my_hash_map &assign_from_map = assign_map._buckets;
  for (int i = 0; i < _capacity; ++i)
  {
    const bucket &get_bucket = assign_from_map[i];
    if (!get_bucket.empty ())
    {
      bucket copied_bucket (assign_from_map[i]);
      _buckets[i] = copied_bucket;
    }
  }
  return *this;
}

template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[] (const KeyT &key)
{
  if (!contains_key (key))
  {
    insert (key, ValueT ());
  }
  return at (key);
}

template<class KeyT, class ValueT>
const ValueT &HashMap<KeyT, ValueT>::operator[] (const KeyT &key) const
{
  if (!contains_key (key))
  {
    return _default_value;
  }
  return at (key);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator== (const HashMapT &compare_map) const
{
  if (_size != compare_map._size)
  {
    return false;
  }
  for (int i = 0; i < compare_map._capacity; i++)
  {
    const bucket &my_bucket = compare_map._buckets[i];
    for (int j = 0; j < (int) my_bucket.size (); j++)
    {
      const pair &cur_pair = my_bucket[j];
      const KeyT &key = cur_pair.first;
      const ValueT &value = cur_pair.second;
      if (!contains_key (key))
      { return false; }
      else
      {
        if (at (key) != value)
        { return false; }
      }
    }
  }
  return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!= (const HashMapT &compare_map) const
{
  return !operator== (compare_map);
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::hashing (const KeyT &key) const
{
  size_t key_hash = std::hash<KeyT>{} (key);
  return key_hash & (this->_capacity - 1);
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::rehashing (int new_capacity)
{
  HashMapT temp (*this);
  delete[] _buckets;
  _capacity = new_capacity, _size = 0;
  _buckets = new bucket[new_capacity];
  for (int i = 0; i < temp._capacity; i++)
  {
    const bucket &my_bucket = temp._buckets[i];
    for (int j = 0; j < (int) my_bucket.size (); j++)
    {
      const pair &cur_pair = my_bucket[j];
      const KeyT &key = cur_pair.first;
      const ValueT &value = cur_pair.second;
      insert (key, value);
    }
  }
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::find_new_capacity ()
{
  int new_capacity = _capacity;
  double new_load_factor = get_load_factor ();
  if (new_load_factor > UPPER_LOAD_FACTOR)
  {
    new_capacity *= 2;
  }
  else
  {
    while (new_load_factor < LOWER_LOAD_FACTOR)
    {
      new_capacity /= 2;
      new_load_factor = double (_size) / (double) new_capacity;
    }
  }
  if (new_capacity < 1)
  { new_capacity = 1; }
  return new_capacity;
}

#endif //_HASHMAP_HPP_
