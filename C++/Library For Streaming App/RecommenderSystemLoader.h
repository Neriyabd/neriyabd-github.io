
#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H

#include "RecommenderSystem.h"

class RecommenderSystemLoader
{

 private:
  static void
  /**
   * create a user object based on input and insert the user into movie_details
   * @param system - recommendation system to fill
   * @param movie_details - vector of name and year of movies
   */
  add_sp_movie_to_rs (up_system &system, std::string &line);

 public:
  RecommenderSystemLoader () = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return shared pointer to a RecommenderSystem which was created with
   * those movies
   */
  static up_system create_rs_from_movies_file (const std::string &
  movies_file_path) noexcept (false);
};

#endif //RECOMMENDERSYSTEMLOADER_H
