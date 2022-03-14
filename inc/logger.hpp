#pragma once

#include<vector>
#include<ctime>
#include<string>
#include<iostream>

enum class LogType
{
  Msg = 0,
  Warning = 1,
  Error = 2
};

struct Log
{
  time_t time;
  LogType type;
  std::string text;

  Log(time_t _time, LogType _type, std::string _text);
};

std::ostream& operator<<(std::ostream& stream, const Log& log);


class Logger
{
private:
  static Logger* instance;

  std::vector<Log> logs;

public:
  Logger();
  ~Logger();

  static void log(LogType type, const std::string& text);
  static bool dump();
  static void clear();
};