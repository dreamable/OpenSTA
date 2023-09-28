

#include "Machine.hh"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <thread>

#include "StaConfig.hh"
#include "StringUtil.hh"

namespace sta {

static struct timeval elapsed_begin_time_;

int
processorCount()
{
  return std::thread::hardware_concurrency();
}

void
initElapsedTime()
{
  struct timezone tz;
  gettimeofday(&elapsed_begin_time_, &tz);
}

double
elapsedRunTime()
{
  static struct timeval time;
  struct timezone tz;
  gettimeofday(&time, &tz);
  return time.tv_sec - elapsed_begin_time_.tv_sec
    + (time.tv_usec - elapsed_begin_time_.tv_usec) * 1E-6;
}

double
userRunTime()
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  return rusage.ru_utime.tv_sec + rusage.ru_utime.tv_usec * 1e-6;
}

double
systemRunTime()
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  return rusage.ru_stime.tv_sec + rusage.ru_stime.tv_usec * 1e-6;
}

size_t
memoryUsage()
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  return rusage.ru_maxrss;
}

} // namespace
