#pragma once

#include"profile.hpp"

class Compiler
{
private:
  Profile profile;

public:
  Compiler(Profile& _profile);
  ~Compiler();

  bool compile();
  bool link();
};