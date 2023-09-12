#include "Movie.h"
#include <utility>

#define HASH_START 17
#define RES_MULT 31

/** documentation for functions in header file */

Movie::Movie (const std::string &name, int year)
{
  _name = name;
  _year = year;
}

const std::string &Movie::get_name () const
{
  return this->_name;
}

const int &Movie::get_year () const
{
  return this->_year;
}

bool operator< (const Movie &lhs, const Movie &rhs)
{
  if (lhs._year < rhs._year)
  {
    return true;
  }
  if (lhs._year == rhs._year)
  {
    if (lhs._name.compare (rhs._name) < 0)
    {
      return true;
    }
  }
  return false;
}

std::ostream &operator<< (std::ostream &stream, const Movie &movie)
{
  stream << movie._name << " " << "(" << movie._year << ")" << std::endl;
  return stream;
}

/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash (const sp_movie &movie)
{
  std::size_t res = HASH_START;
  res = res * RES_MULT + std::hash<std::string> () (movie->get_name ());
  res = res * RES_MULT + std::hash<int> () (movie->get_year ());
  return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1 - shared pointer to movie object
 * @param m2 - shared pointer to movie object
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2)
{
  return !(*m1 < *m2) && !(*m2 < *m1);
}

/**
 * compare function used for ordered map between 2 movie objects
 * @param m1 - shared pointer to movie object
 * @param m2 - shared pointer to movie object
 * @return true or false based on < operator in movie class
 */
bool sp_movie_compare (const sp_movie &m1, const sp_movie &m2)
{
  return *m1 < *m2;
}
