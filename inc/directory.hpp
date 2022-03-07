#pragma once

#include<vector>
#include<string>

// gather files with specific extension recursivly
std::vector<std::string> gatherFiles(const std::string& root, const std::string& ext);