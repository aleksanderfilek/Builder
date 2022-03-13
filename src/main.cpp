#include<iostream>

#include"profile.hpp"
#include"directory.hpp"

int main(int argc, char* argv[])
{
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

  auto includeFiles = gatherFiles(".", ".hpp");
  auto sourceFiles = gatherFiles(".", ".cpp");
  
  

  return 0;
}

// #include<iostream>
// #include <windows.h>
// #include <vector>
// #include <string>
// #include <filesystem>

// #include <iostream>
// #include <vector>
// #include <dirent.h>

// using std::cout; using std::cin;
// using std::endl; using std::vector;

// DIR *dir;
  //  struct dirent *diread;
  //   vector<char *> files;

  //   if ((dir = opendir(".")) != nullptr) {
  //       while ((diread = readdir(dir)) != nullptr) {
  //           files.push_back(diread->d_name);
  //           cout<<diread->d_name<<endl;
  //       }
  //       closedir (dir);
  //   } else {
  //       perror ("opendir");
  //       return EXIT_FAILURE;
  //   }

  //   for (auto file : files) cout << file << "| ";
  //   cout << endl;
  // if(argc == 0)
  // {
  //   std::cout<<"No directory path"<<std::endl;
  //   exit(-1);
  // }
// SECURITY_ATTRIBUTES sa;
//     sa.nLength = sizeof(sa);
//     sa.lpSecurityDescriptor = NULL;
//     sa.bInheritHandle = TRUE;       

//     HANDLE h = CreateFile(TEXT("out.log"),
//         FILE_APPEND_DATA,
//         FILE_SHARE_WRITE | FILE_SHARE_READ,
//         &sa,
//         OPEN_ALWAYS,
//         FILE_ATTRIBUTE_NORMAL,
//         NULL );

//     PROCESS_INFORMATION pi; 
//     STARTUPINFO si;
//     BOOL ret = FALSE; 
//     DWORD flags = CREATE_NO_WINDOW;

//     ZeroMemory( &pi, sizeof(PROCESS_INFORMATION) );
//     ZeroMemory( &si, sizeof(STARTUPINFO) );
//     si.cb = sizeof(STARTUPINFO); 
//     si.dwFlags |= STARTF_USESTDHANDLES;
//     si.hStdInput = NULL;
//     si.hStdError = h;
//     si.hStdOutput = h;

//     TCHAR cmd[]= TEXT("g++ src/main.cpp -o e.exe");
//     ret = CreateProcess(NULL, cmd, NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi);

//     if ( ret ) 
//     {
//         CloseHandle(pi.hProcess);
//         CloseHandle(pi.hThread);
//         return 0;
//     }

//     return -1;