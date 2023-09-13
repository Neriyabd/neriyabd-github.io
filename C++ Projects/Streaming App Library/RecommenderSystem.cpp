#include "RecommenderSystem.h"

RecommenderSystem::RecommenderSystem () : _database (sp_movie_compare)
{}

sp_movie RecommenderSystem::add_movie (const std::string &name, int year, const
std::vector<double> &features)
{
  for (const auto& it : features)
  {
    if (it < MIN_FEAT_NUMBER || it > MAX_FEAT_NUMBER)
    {
    throw std::out_of_range (OUT_OF_RANGE_MSG);
    }
  }
  sp_movie movie = std::make_shared<Movie> (name, year);
  this->_database[movie] = features;
  return movie;
}

sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
{
  rank_map users_rank_map = user.get_ranks ();
  subtract_avg_rank_map (users_rank_map);
  doubles_vector preferences_vec = create_preferences_vec (users_rank_map);
  sp_movie movie = find_similar_movie (user, preferences_vec);
  return movie;
}

sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  sp_movie movie;
  const rank_map &user_map = user.get_ranks ();
  double max_movie_score = 0;
  for (const auto &it: _database)
  {
    const sp_movie &current_movie = it.first;
    auto pair = user_map.find (it.first);
    if (pair == user.get_ranks ().end ())
    {
      double movie_score = predict_movie_score (user, current_movie, k);
      if (movie_score > max_movie_score)
      {
        max_movie_score = movie_score;
        movie = current_movie;
      }
    }
  }
  return movie;
}

double
RecommenderSystem::predict_movie_score (const RSUser &user,
                                        const sp_movie &movie, int k)
{
  my_set similar_movies;
  doubles_vector unranked_vec_feat = _database[movie];
  for (const auto &it: user.get_ranks ())
  {
    const auto &current_movie = it.first;
    doubles_vector ranked_feat = _database[current_movie];
    double value = diagnose_formula (unranked_vec_feat, ranked_feat);
    similar_movies.insert ({value, current_movie});
  }
  double value = calc_value_of_movie (similar_movies, k, user);
  return value;
}

double
RecommenderSystem::calc_value_of_movie (my_set &similar_movies,
                                        int num_movies_to_calc,
                                        const RSUser &user)
{
  double numerator = 0, denominator = 0;
  int summed_movies = 0;
  const rank_map &user_map = user.get_ranks ();
  for (auto it = similar_movies.rbegin (); it != similar_movies.rend (); it++)
  {
    const double &feat_value = it->first;
    const sp_movie &current_movie = it->second;
    if (summed_movies >= num_movies_to_calc)
    { break; }
    {
      double users_rank_cur_movie = user_map.find (current_movie)->second;
      numerator += (feat_value * users_rank_cur_movie);
      denominator += feat_value;
    }
    summed_movies++;
  }
  return numerator / denominator;
}

sp_movie RecommenderSystem::get_movie (const std::string &name,
                                       int year) const
{
  sp_movie movie_ptr = std::make_shared<Movie> (name, year);
  auto it = _database.find (movie_ptr);
  if (it != _database.end ())
  {
    return it->first;
  }
  return nullptr;
}

double
RecommenderSystem::calc_stand_product (const doubles_vector &vec1,
                                       const doubles_vector &vec2)
{
  double sum = 0;
  for (int i = 0; i < (int) vec1.size (); ++i)
  {
    sum += vec1[i] * vec2[i];
  }
  return sum;
}

double RecommenderSystem::get_norm_of_vector (const doubles_vector &vec)
{
  double norm = 0;
  for (double coord: vec)
  {
    norm += coord * coord;
  }
  return sqrt (norm);
}

sp_movie
RecommenderSystem::find_similar_movie (const RSUser &user,
                                       const doubles_vector &preferences_vec)
{
  sp_movie movie;
  const rank_map &user_map = user.get_ranks ();
  double minimal_ang = 0;
  for (const auto &it: _database)
  {
    auto pair = user_map.find (it.first);
    if (pair == user_map.end ())
    {
      const doubles_vector &feature_vector = it.second;
      double diagnose_value = diagnose_formula
          (preferences_vec, feature_vector);
      if (diagnose_value > minimal_ang)
      {
        minimal_ang = diagnose_value;
        movie = it.first;
      }
    }
  }
  return movie;
}

double
RecommenderSystem::diagnose_formula (const doubles_vector &preferences_vec,
                                     const doubles_vector &feature_vector)
{
  double vec_product = calc_stand_product (feature_vector, preferences_vec);
  double norm_product = (get_norm_of_vector (preferences_vec)
                         * get_norm_of_vector (feature_vector));
  double diagnose_value = vec_product / norm_product;
  return diagnose_value;
}

doubles_vector
RecommenderSystem::create_preferences_vec (rank_map &users_rank_map)
{
  bool first_loop = true;
  doubles_vector vector;
  for (const auto &rank_pair: users_rank_map)
  {
    double average_rank = rank_pair.second;
    doubles_vector feat_vec = _database[rank_pair.first];
    {
      for (int i = 0; i < (int) feat_vec.size (); ++i)
      {
        if (first_loop)
        {
          vector.push_back (average_rank * feat_vec[i]);
        }
        else
        {
          vector[i] += (average_rank * feat_vec[i]);
        }
      }
      first_loop = false;
    }
  }
  return vector;
}

void RecommenderSystem::subtract_avg_rank_map (rank_map &users_rank_map)
{
  double average_rank = 0;
  for (const auto &it: users_rank_map)
  {
    double rank = it.second;
    average_rank += rank;
  }
  average_rank = average_rank / (double) users_rank_map.size ();
  for (auto &it: users_rank_map)
  {
    {
      it.second -= average_rank;
    }
  }
}

std::ostream &operator<< (std::ostream &stream,
                          const RecommenderSystem &system)
{
  for (const auto &it: system._database)
  {
    stream << *(it.first);
  }
  return stream;
}