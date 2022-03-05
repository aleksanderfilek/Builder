#pragma once

#include<string>
#include<vector>

enum class Type 
{
  Executable,
  SharedLibrary,
  StaticLibrary
};

struct Profile
{
  std::string name;
  Type type;
  std::string compiler;
  std::string outputDir;
  std::vector<std::string> includesDir;
  std::vector<std::string> libsDir;
  std::vector<std::string> libs;
  std::vector<std::string> compilerDefines;
  std::vector<std::string> builderDefines;

  bool load(const std::string& path);
};
