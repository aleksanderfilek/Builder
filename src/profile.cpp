#include"profile.hpp"
#include"json.hpp"

#include<iostream>
#include<fstream>

using json = nlohmann::json;

NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
  {Type::Executable, "Executable"},
  {Type::SharedLibrary, "SharedLibrary"},
  {Type::StaticLibrary, "StaticLibrary"},
});

bool Profile::load(const std::string& path)
{
  std::ifstream reader(path);
  if(!reader.is_open())
  {
    std::cout<<"[Error] Could not load profile: "<<path<<std::endl;
    return false;
  }

  json file;
  reader >> file;

  reader.close();

  // obligatory
  file.at("Name").get_to(name);
  file.at("Type").get_to(type);
  file.at("Compiler").get_to(compiler);

  // optional 
  if (file.find("OutputDir") != file.end())
    file.at("OutputDir").get_to(outputDir);
  if (file.find("IncludesDir") != file.end())
    file.at("IncludesDir").get_to(includesDir);
  if (file.find("LibsDir") != file.end())
    file.at("LibsDir").get_to(libsDir);
  if (file.find("Libs") != file.end())
    file.at("Libs").get_to(libs);
  if (file.find("CompilerDefines") != file.end())
    file.at("CompilerDefines").get_to(compilerDefines);
  if (file.find("BuilderDefines") != file.end())
    file.at("BuilderDefines").get_to(builderDefines);

  return true;
}