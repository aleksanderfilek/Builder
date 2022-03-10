#pragma once

#include<vector>
#include<string>

// gather files with specific extension recursively
std::vector<std::string> gatherFiles(const std::string& root, const std::string& ext);

// check if directory exists
bool directoryExsists(const std::string& path);

// check if file exists
bool fileExsists(const std::string& path);

// create directory recursively
bool createDirectory(const std::string& path);