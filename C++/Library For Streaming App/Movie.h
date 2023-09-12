#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#define HASH_START 17
#define OUT_OF_RANGE_MSG "Exception: Out of Range Error"
#define RUN_TIME_ERROR_MSG "Exception: RuntimeError"
#define NAME_STR "name: "
#define MAX_FEAT_NUMBER 10
#define MIN_FEAT_NUMBER 1
#define HYPHEN '-'
#define SPACE ' '
#define HAS_NO_VALUE "NA"

class Movie;

/** typedef */
// typedef for shared pointer for movie class
typedef std::shared_ptr<Movie> sp_movie;
// typedef for pointer to hush function to use in unordered map
typedef std::size_t (*hash_func) (const sp_movie &movie);
// typedef for pointer to equal function to use in unordered map
typedef bool (*equal_func) (const sp_movie &m1, const sp_movie &m2);
// typedef for compare function between movies objects
typedef bool (*compare_func) (const sp_movie &m1, const sp_movie &m2);
// type def for an ordered map for use of the database to store all data
typedef std::map<sp_movie, std::vector<double>, compare_func> ordered_map;
// typedef for vectors of doubles
typedef std::vector<double> doubles_vector;
// typedef for a vector of pair of double and share pointer to movie
typedef std::set<std::pair<double, sp_movie>> my_set;
// declaration of hush function - documentation in movie.cpp file
std::size_t sp_movie_hash (const sp_movie &movie);
// declaration of equal function - documentation in movie.cpp file
bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2);
// declaration of compare function - documentation in movie.cpp file
bool sp_movie_compare (const sp_movie &m1, const sp_movie &m2);

class Movie
{
 public:
  /**
   * constructor
   * @param name: name of movie
   * @param year: year it was made
   */
  Movie (const std::string &name, int year);

  /**
   * returns the name of the movie
   * @return const ref to name of movie
   */
  const std::string &get_name () const;

  /**
   * returns the year the movie was made
   * @return year movie was made
   */
  const int &get_year () const;

  /**
   * operator< for two movies
   * @param rhs: right hand side
   * @param lhs: left hand side
   * @return returns true if (rhs.year) < lhs.year or (rhs.year == lhs.year
   * & rhs.name == lhs.name) else return false
   */
  friend bool operator< (const Movie &lhs, const Movie &rhs);

  /**
   * operator<< for movie
   * @param os ostream to output info with
   * @param movie movie to output
   */
  friend std::ostream &operator<< (std::ostream &stream, const Movie &movie);

 private:
  std::string _name;
  int _year;
};

#endif //MOVIE_H
