
#ifndef RECOMMENDERSYSTEM_H
#define RECOMMENDERSYSTEM_H

#include "RSUser.h"

class RecommenderSystem
{
 public:
  /**
   * initialize default constructor for Recommender System class
   */
  explicit RecommenderSystem ();

  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie
  add_movie (const std::string &name, int year,
             const std::vector<double> &features);

  /**
   * a function that calculates the movie with highest score based on
   * movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const RSUser &user);

  /**
   * a function that calculates the movie with highest predicted score based
   * on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k - number of movies to calc from
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const RSUser &user, int k);

  /**
   * Predict a user rating for a movie given argument using item cf procedure
   * with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const RSUser &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * output stream operator
   * @param stream the output stream
   * @param system the recommendation system
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &stream,
                                   const RecommenderSystem &system);

 private:
  /** recommendation system */
  ordered_map _database;
  /**
   * calculate the average rank of a user ranking and
   * subtract it from user map rank of movies
   * @param users_rank_map - ranking to use
   */
  static void subtract_avg_rank_map (rank_map &users_rank_map);
  /**
   * create a vector of doubles based on the ranking of the ranked movies
   * the user's already ranked.
   * @param users_rank_map - ranking to use
   * @return a vector of doubles
   */
  doubles_vector create_preferences_vec (rank_map &users_rank_map);
  /**
   * calculate the similarity between the preferences_vec and the features
   * that the user's didn't ranked
   * @param users_rank_map - ranking to use
   * @param preferences_vec - a vector of doubles that contain pref score of
   * user's movies
   * @return shared pointer of the highest similarity movie
   */
  sp_movie find_similar_movie (const RSUser &user,
                               const doubles_vector &preferences_vec);
  /**
   * calculate the standard product of 2 given vectors
   * @param vec1 - features vector of doubles
   * @param vec2 - features vector of doubles
   * @return the result as a double
   */
  static double calc_stand_product (const doubles_vector &vec1,
                                    const doubles_vector &vec2);
  /**
   * calculate the norm of a vector
   * @param vec - a vector of doubles
   * @return norm value of vector
   */
  static double get_norm_of_vector (const doubles_vector &vec);
  /**
   * calculate the similarity angle between 2 vectors
   * @param preferences_vec - vector of preferences user's feature
   * @param feature_vector - vector of features of type double
   * @return a double of similarity value
   */
  static double
  diagnose_formula (const doubles_vector &preferences_vec,
                    const doubles_vector &feature_vector);
  /**
   * find the value of a the current movie based on formula
   * @param similar_movies - a set of a sorted similar movies to movie
   * @param num_movies_to_calc - number of movies to calc from
   * @param user - user's class object
   * @return double of similarity score of movie
   */
  static double calc_value_of_movie (my_set &similar_movies,
                                     int num_movies_to_calc,
                                     const RSUser &user);

};

#endif //RECOMMENDERSYSTEM_H
