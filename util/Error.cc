

#include "Error.hh"

#include <cstdlib>
#include <cstdio>

#include "StringUtil.hh"

namespace sta {

Exception::Exception() :
  std::exception()
{
}

ExceptionMsg::ExceptionMsg(const char *msg) :
  Exception(),
  msg_(msg)
{
}

const char *
ExceptionMsg::what() const noexcept
{
  return msg_.c_str();
}

ExceptionLine::ExceptionLine(const char *filename,
			     int line) :
  Exception(),
  filename_(filename),
  line_(line)
{
}

FileNotReadable::FileNotReadable(const char *filename) :
  filename_(filename)
{
}

const char *
FileNotReadable::what() const noexcept
{
  return stringPrintTmp("cannot read file %s.", filename_);
}

FileNotWritable::FileNotWritable(const char *filename) :
  filename_(filename)
{
}

const char *
FileNotWritable::what() const noexcept
{
  return stringPrintTmp("cannot write file %s.", filename_);
}

} // namespace
