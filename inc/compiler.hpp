#pragma once

#include"profile.hpp"

#include<vector>
#include<set>
#include<string>

class Compiler
{
private:
  Profile profile;

  std::vector<std::string> sources;
  std::set<std::string> headers;
  std::vector<std::string> objects;

public:
  Compiler(Profile& _profile);
  ~Compiler();

  void findFiles();
  bool compile();
  bool link();

  void runProcess(int id, const std::string& cmd);
};

