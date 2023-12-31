
#ifndef USER_H
#define USER_H

#include "Movie.h"

class RecommenderSystem;
// typedef for an unordered map
typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;
// typedef for shared pointer to RecommenderSystem
typedef std::shared_ptr<RecommenderSystem> sp_system;
// typedef for unique pointer to RecommenderSystem
typedef std::unique_ptr<RecommenderSystem> up_system;
// typedef for a vector of strings
typedef std::vector<std::string> strings_vector;

class RSUser
{
 public:
  /**
   * Constructor to initialize a User's object
   */
  RSUser (std::string &username, rank_map &user_map, sp_system &recommend_sys);

  /**
   * a getter for the user's name
   * @return the username
   */
  const std::string &get_name () const;

  /**
   * function for adding a movie to the DB
   * @param movie a Movie object
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   * @return true for success, false otherwise
   */
  void add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features,
                        double rate);

  /**
   * a getter for the ranks map
   * @return a user's rank map
   */
  const rank_map &get_ranks () const;

  /**
   * returns a recommendation according to the movie's content
   * @return shared ptr to recommendation movie
   */
  sp_movie get_recommendation_by_content () const;

  /**
   * returns a recommendation according to the similarity recommendation method
   * @param k the number of the most similar movies to calculate by
   * @return shared ptr to recommendation movie
   */
  sp_movie get_recommendation_by_cf (int k) const;

  /**
   * predicts the score for a given movie
   * @param name the name of the movie
   * @param year the year the movie was created
   * @param k the parameter which represents the number of the most
   * similar movies to predict the score by
   * @return predicted score for the given movie
   */
  double
  get_prediction_score_for_movie (const std::string &name, int year,
                                  int k) const;

  /**
   * output stream operator
   * @param os the output stream
   * @param user the user
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &stream, const RSUser &user);

 private:
  const std::string _username;
  rank_map _rank_map;
  sp_system _recommend_sys;
};

#endif //USER_H
