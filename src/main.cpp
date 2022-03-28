#include<iostream>

#include"compiler.hpp"
#include"logger.hpp"

int main(int argc, char* argv[])
{
  Logger logger;

  if(argc < 2)
  {
    std::cout<<"[Error] Too few arguments"<<std::endl;
    return -1;
  }

  Profile profile;
  if(!profile.load(argv[1]))
  {
    return -1;
  }

  Compiler compiler(profile);
  compiler.findFiles();
  compiler.compile();
  compiler.link();

  logger.dump();

  return 0;
}