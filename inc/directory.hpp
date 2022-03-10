#pragma once

#include<vector>
#include<string>

// gather files with specific extension recursivly
std::vector<std::string> gatherFiles(const std::string& root, const std::string& ext);

bool directoryExsists(const std::string& path);
bool fileExsists(const std::string& path);