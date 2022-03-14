#include"logger.hpp"
#include"directory.hpp"

#include<fstream>
#include<algorithm>
#include<cstring>

Logger* Logger::instance = nullptr;

static const std::string logTypeStr[] = { "Msg", "Warning", "Error" };

Log::Log(time_t _time, LogType _type, std::string _text)
  : time(_time), type(_type), text(_text) {}

std::ostream& operator<<(std::ostream& stream, const Log& log)
{
  char* ctimeStr = ctime(&log.time);
  std::string timeStr(ctimeStr, 0, strlen(ctimeStr)-1);
  stream<<timeStr<<" ["<<logTypeStr[(int)log.type]<<"] "<<log.text;
  return stream;
}

Logger::Logger()
{
  instance = this;
}

Logger::~Logger()
{

}

void Logger::log(LogType type, const std::string& text)
{
  time_t currentTime;
  time(&currentTime);
  Log log(currentTime, type, text);

  instance->logs.push_back(log);

  std::cout<<log<<std::endl;
}

bool Logger::dump()
{
  createDirectory(".builder/logs");

  time_t currentTime;
  time(&currentTime);
  char* ctimeStr = ctime(&currentTime);
  std::string timeStr(ctimeStr, 0, strlen(ctimeStr)-1);

  std::string fileName(".builder/logs/log_");
  fileName.append(timeStr);
  fileName.append(".txt");


  std::replace(fileName.begin(), fileName.end(), ' ', '_');
  std::replace(fileName.begin(), fileName.end(), ':', '_');
  std::ofstream file(fileName);
  if(!file.is_open())
  {
    return false;
  }

  for(auto log: instance->logs)
  {
    file<<log<<std::endl;
  }

  file.close();

  return true;
}

void Logger::clear()
{
  instance->logs.clear();
}