#include "RecommenderSystemLoader.h"

up_system RecommenderSystemLoader::create_rs_from_movies_file
    (const std::string &movies_file_path) noexcept (false)
{
  up_system system = std::make_unique<RecommenderSystem> ();
  std::fstream file;
  file.open (movies_file_path, std::ios::in);
  if (!file)
  {
    file.close ();
    throw std::runtime_error (RUN_TIME_ERROR_MSG);
  }
  std::string line;
  strings_vector movie_details;
  while (std::getline (file, line))
  {
    add_sp_movie_to_rs (system, line);
  }
  file.close ();
  return system;
}

void
RecommenderSystemLoader::add_sp_movie_to_rs (up_system &system,
                                             std::string &line)
{
  size_t pos = line.find (HYPHEN);
  line[pos] = SPACE;
  std::string buffer;
  std::istringstream iss (line);
  doubles_vector features;
  std::string str_year;
  std::string name;
  iss >> name >> str_year;
  int year = std::stoi (str_year);
  while (iss >> buffer)
  {
    double num = std::stod (buffer);
    if (num < MIN_FEAT_NUMBER || num > MAX_FEAT_NUMBER)
    {
      throw std::out_of_range (OUT_OF_RANGE_MSG);
    }
    features.push_back (num);
  }
  system->add_movie (name, year, features);
}
