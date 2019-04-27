
#include "DDSLog.h"

#include <cstdio>
#include <cstdarg>

#include <stdexcept>

static DDSLog::LogLevel s_LogLevel = DDSLog::kInfo;

void DDSLog::SetLogLevel(LogLevel level)
{
  s_LogLevel = level;
}

void DDSLog::LogInfo(const char * fmt, ...)
{
  if (s_LogLevel == DDSLog::kNone)
  {
    return;
  }

  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  printf("\n");
}

void DDSLog::LogInfo(const std::string & str)
{
  if (s_LogLevel == DDSLog::kNone)
  {
    return;
  }

  printf("%s\n", str.c_str());
}

void DDSLog::LogVerbose(const char * fmt, ...)
{
  if (s_LogLevel == DDSLog::kNone || s_LogLevel == DDSLog::kInfo)
  {
    return;
  }

  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  printf("\n");
}

void DDSLog::LogVerbose(const std::string & str)
{
  if (s_LogLevel == DDSLog::kNone || s_LogLevel == DDSLog::kInfo)
  {
    return;
  }

  printf("%s\n", str.c_str());
}

void DDSLog::LogError(const char * fmt, ...)
{
  char buffer[4096];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  fprintf(stderr, "!!FATAL ERROR: %s\n", buffer);

  throw std::runtime_error(buffer);
}

