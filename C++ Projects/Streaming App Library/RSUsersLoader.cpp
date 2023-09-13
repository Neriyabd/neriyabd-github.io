#include "RSUsersLoader.h"

/** documentation for functions in header file */

string_int_pair_vec
RSUsersLoader::read_movie_name_and_year (std::string &input, bool &is_first)
{
  string_int_pair_vec movie_year_vec;
  std::replace (input.begin (), input.end (), HYPHEN, SPACE);
  std::istringstream iss (input);
  std::string movie_name, year;
  while (iss >> movie_name >> year)
  {
    movie_year_vec.emplace_back (movie_name, std::stoi (year));
  }
  is_first = false;
  return movie_year_vec;
}

std::vector<RSUser>
RSUsersLoader::create_users_from_file (const std::string &users_file_path,
                                       const up_system rs) noexcept (false)
{
  sp_system sp_sys = std::make_shared<RecommenderSystem> (*rs);
  std::fstream file;
  std::string input, username;
  string_int_pair_vec movie_details_vec;
  std::vector<RSUser> vector_of_users;
  open_loader_user_file (users_file_path, file);
  bool is_first = true;
  while (std::getline (file, input))
  {
    std::istringstream iss (input);
    if (is_first)
    {
      movie_details_vec = read_movie_name_and_year (input, is_first);
      continue;
    }
    rank_map users_map (HASH_START, sp_movie_hash, sp_movie_equal);
    iss >> username;
    for (auto &it: movie_details_vec)
    {
      add_to_rank_map (sp_sys, iss, users_map, it, file);
    }
    auto user = RSUser (username, users_map, sp_sys);
    vector_of_users.push_back (user);
  }
  file.close ();
  return vector_of_users;
}

void
RSUsersLoader::open_loader_user_file (const std::string &users_file_path,
                                      std::fstream &file)
{
  file.open (users_file_path, std::ios::in);
  if (!file)
  {
    throw std::runtime_error (RUN_TIME_ERROR_MSG);
  }
}

void
RSUsersLoader::add_to_rank_map (const sp_system &rs, std::istringstream &iss,
                                rank_map &users_map, const string_int_pair &it,
                                std::fstream &file)
{
  std::string ranking;
  iss >> ranking;
  if (ranking == HAS_NO_VALUE)
  {
    return;
  }
  else
  {
    double conv_feat = std::stod (ranking);
    if (conv_feat < MIN_FEAT_NUMBER || conv_feat > MAX_FEAT_NUMBER)
    {
      file.close ();
      throw std::out_of_range (RUN_TIME_ERROR_MSG);
    }
    sp_movie movie = rs->get_movie (it.first, it.second);
    users_map[movie] = conv_feat;
  }
}
