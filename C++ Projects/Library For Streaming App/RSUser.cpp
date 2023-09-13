#include "RSUser.h"
#include "RecommenderSystem.h"

/** documentation for functions in header file */

RSUser::RSUser (std::string &username, rank_map &user_map,
                sp_system &recommend_sys)
    : _username (username), _rank_map (user_map),
      _recommend_sys (recommend_sys)
{}

void RSUser::add_movie_to_rs (const std::string &name, int year,
                              const std::vector<double> &features,
                              double rate)
{
  if (rate < MIN_FEAT_NUMBER || rate > MAX_FEAT_NUMBER)
  {
    throw std::out_of_range (OUT_OF_RANGE_MSG);
  }
  sp_movie cur_movie = _recommend_sys->add_movie (name, year, features);
  this->_rank_map[cur_movie] = rate;
}

const std::string &RSUser::get_name () const
{
  return this->_username;
}

const rank_map &RSUser::get_ranks () const
{
  return this->_rank_map;
}

sp_movie RSUser::get_recommendation_by_content () const
{
  return _recommend_sys->recommend_by_content (*this);
}

sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  return _recommend_sys->recommend_by_cf (*this, k);
}

double
RSUser::get_prediction_score_for_movie (const std::string &name, int year,
                                        int k) const
{
  sp_movie movie_ptr = _recommend_sys->get_movie (name, year);
  return _recommend_sys->predict_movie_score (*this, movie_ptr, k);
}

std::ostream &operator<< (std::ostream &stream, const RSUser &user)
{
  stream << NAME_STR << user._username << std::endl;
  stream << *user._recommend_sys;
  return stream;
}




