#include"compiler.hpp"
#include"directory.hpp"
#include"logger.hpp"

#ifdef _WIN32
  #include<windows.h>
#endif

Compiler::Compiler(Profile& _profile)
  : profile(_profile)
{

}

Compiler::~Compiler()
{

}

void Compiler::findFiles()
{
  std::vector<std::string> includeFiles = gatherFiles(".", ".hpp");
  for(auto file: includeFiles)
  {
    size_t startPosition = file.find_first_of("/") + 1;
    size_t endPosition = file.find_last_of("/");
    headers.insert(std::string(file, startPosition, endPosition - startPosition));
  }

  sources = gatherFiles(".", ".cpp");
  for(auto& file: sources)
  {
    size_t startPosition = file.find_first_of("/") + 1;
    file = std::string(file, startPosition, file.length() - startPosition);
  }
}

bool Compiler::compile()
{
  std::string startCmd;
  startCmd.append(profile.compiler);

  for(auto define: profile.compilerDefines)
  {
    startCmd.append(" -D");
    startCmd.append(define);
  }

  startCmd.append(" -c");

  if(profile.type == Type::SharedLibrary)
  {
    startCmd.append(" -fPIC");
  }

  for(auto header: headers)
  {
    startCmd.append(" -I");
    startCmd.append(header);
  }

  for(auto header: profile.includesDir)
  {
    startCmd.append(" -I");
    startCmd.append(header);
  }

  std::string endCmd;

  for(int i = 0; i < sources.size(); i++)
  {
    std::string text("[");
    text.append(std::to_string(i+1));
    text.append("/");
    text.append(std::to_string(sources.size()));
    text.append("] ");
    text.append(sources[i]);

    size_t slashPosition = sources[i].find_last_of("/");
    std::string objectFilePath(".builder/obj/");
    objectFilePath.append(sources[i], 0, slashPosition);
    createDirectory(objectFilePath);

    size_t extPosition = sources[i].find_last_of(".") + 1;
    std::string objectName(".builder/obj/");
    objectName.append(sources[i], 0, extPosition);
    objectName.append("o");

    objects.push_back(objectName);

    std::string cmd;
    cmd.append(startCmd);
    cmd.append(" ");
    cmd.append(sources[i]);
    cmd.append(" -o ");
    cmd.append(objectName);
    cmd.append(endCmd);

    runProcess(i,cmd);

    Logger::log(LogType::Msg, text);
  }

  return true;
}

bool Compiler::link()
{
  std::string cmd;
  cmd.append(profile.compiler);

  for(auto define: profile.compilerDefines)
  {
    cmd.append(" -D");
    cmd.append(define);
  }

  for(auto lib: profile.libsDir)
  {
    cmd.append(" -L");
    cmd.append(lib);
  }

  cmd.append(" -o ");
  cmd.append(profile.outputDir);
  cmd.append("/");
  cmd.append(profile.name);


  for(int i = 0; i < objects.size(); i++)
  {
    cmd.append(" ");
    cmd.append(objects[i]);
  }

  for(int i = 0; i < profile.libs.size(); i++)
  {
    cmd.append(" ");
    cmd.append(profile.libs[i]);
  }

  if(profile.type == Type::SharedLibrary)
  {
    cmd.append(" -shared");
  }

  runProcess(sources.size(),cmd);
  Logger::log(LogType::Msg, "Linked");

  return true;
}

void Compiler::runProcess(int id, const std::string& cmd)
{
  createDirectory(".builder/tmp");

#ifdef _WIN32
  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof(sa);
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;       

  std::string outFileName(".builder/tmp/out_");
  outFileName.append(std::to_string(id));
  outFileName.append(".log");

  HANDLE h = CreateFile(TEXT(outFileName.c_str()),
      FILE_APPEND_DATA,
      FILE_SHARE_WRITE | FILE_SHARE_READ,
      &sa,
      OPEN_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL);

  PROCESS_INFORMATION pi; 
  STARTUPINFO si;
  DWORD flags = CREATE_NO_WINDOW;

  ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO); 
  si.dwFlags |= STARTF_USESTDHANDLES;
  si.hStdInput = NULL;
  si.hStdError = h;
  si.hStdOutput = h;

  CreateProcess(NULL, const_cast<char*>(cmd.c_str()), NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi);

  auto ret = WaitForSingleObject(pi.hProcess, INFINITE);

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);


  DeleteFile(TEXT(outFileName.c_str()));
#endif
}