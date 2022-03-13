#include"logger.hpp"

#include<fstream>

Logger* Logger::instance = nullptr;

static const std::string logTypeStr[] = { "Msg", "Warning", "Error" };

Log::Log(time_t _time, LogType _type, std::string _text)
  : time(_time), type(_type), text(_text) {}

std::ostream& operator<<(std::ostream& stream, const Log& log)
{
  stream<<ctime(&log.time)<<" ["<<logTypeStr[(int)log.type]<<"] "<<log.text;
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
}

bool Logger::dump()
{
  time_t currentTime;
  time(&currentTime);

  std::string fileName("Log_");
  fileName.append(ctime(&currentTime));
  fileName.append(".txt");

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

void Logger::print()
{
  for(auto log: instance->logs)
  {
    std::cout<<log<<std::endl;
  }
}

void Logger::clear()
{
  instance->logs.clear();
}