
#ifndef USERFACTORY_H
#define USERFACTORY_H

#include "RecommenderSystem.h"
typedef std::vector<std::pair<std::string, int>> string_int_pair_vec;
typedef std::pair<std::string, int> string_int_pair;

class RSUsersLoader
{
 private:
  /**
   * create a vector of names and a year of a movie
   * @param input - a line from the loader file
   * @param is_first - boolean value to check if its the first line of file
   * @return a vector of movie name and year (string, int)
   */
  static string_int_pair_vec read_movie_name_and_year (std::string
                                                       &input, bool &is_first);
  /**
   * add data to a user's ranked map
   * @param rs - a shared pointer to recommendation system
   * @param iss - string stream to read from
   * @param users_map - user ranking of movies
   * @param it - a pair of movie name and year
   * @param file - path to the loader file
   */
  static void
  add_to_rank_map (const sp_system &rs, std::istringstream &iss,
                   rank_map &users_map, const string_int_pair &it,
                   std::fstream &file);
  /**
   * open the file and check if opened successfully
   * @param users_file_path - a path to the loader file
   * @param file - a reference to a file stream object
   */
  static void
  open_loader_user_file (const std::string &users_file_path,
                         std::fstream &file);

 public:
  RSUsersLoader () = delete;
  /**
   *
   * loads users by the given format with their movie's ranks
   * @param users_file_path a path to the file of the users and their
   * movie ranks
   * @param rs RecommendingSystem for the Users
   * @return vector of the users created according to the file
   */
  static std::vector<RSUser> create_users_from_file (const std::string &
  users_file_path, up_system rs) noexcept (false);
};

#endif //USERFACTORY_H
