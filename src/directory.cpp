#include"directory.hpp"

#include<iostream>
#include<dirent.h>
#include<fstream>

std::vector<std::string> gatherFiles(const std::string& root, const std::string& ext)
{
  DIR *dir;
  dirent *diread;
  std::vector<std::string> files;

  if ((dir = opendir(root.c_str())) != nullptr) 
  {
    int fileCounter = 0;
    while ((diread = readdir(dir)) != nullptr) 
    {
      std::string name = std::string(diread->d_name);

      // skip first directories . and ..
      if(fileCounter++ < 2)
        continue;

      if(diread->d_type == DT_DIR )
      {
        std::string subRoot(root);
        subRoot.append("/");
        subRoot.append(name);
        std::vector<std::string> subFiles = gatherFiles(subRoot, ext);
        for(auto file: subFiles)
        {
          files.push_back(file);
        }
        continue;
      }

      if(name.find(ext) == std::string::npos)
        continue;

      std::string fullName(root);
      fullName.append("/");
      fullName.append(name);
      files.push_back(fullName);
    }
    closedir (dir);
  } 
  else 
  {
    std::cout<<"[Error] Could not open directory: "<<root<<std::endl;
    return std::vector<std::string>();
  }

  return files;
}

bool directoryExsists(const std::string& path)
{
  DIR *dir;
  if((dir = opendir(path.c_str())) != nullptr)
  {
    closedir(dir);
    return true;
  }

  return false;
}

bool fileExsists(const std::string& path)
{
  std::ifstream file(path);

  if(file.is_open())
  {
    file.close();
    return true;
  }

  return false;
}