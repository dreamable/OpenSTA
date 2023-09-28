

#include "ReportStd.hh"

#include <cstdlib>
#include <cstdio>

#include "Report.hh"

namespace sta {

// Output streams that talk to stdout and stderr streams.
class ReportStd : public Report
{
public:
  ReportStd();

protected:
  virtual size_t printConsole(const char *buffer, size_t length);
  virtual size_t printErrorConsole(const char *buffer, size_t length);
};

Report *
makeReportStd()
{
  return new ReportStd;
}

ReportStd::ReportStd() :
  Report()
{
}

size_t
ReportStd::printConsole(const char *buffer, size_t length)
{
  return fwrite(buffer, sizeof(char), length, stdout);
}

size_t
ReportStd::printErrorConsole(const char *buffer, size_t length)
{
  return fwrite(buffer, sizeof(char), length, stderr);
}

} // namespace
