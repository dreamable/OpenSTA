



#include <exception>

#include "Report.hh"

namespace sta {

// Abstract base class for sta exceptions.
class Exception : public std::exception
{
public:
  Exception();
  virtual ~Exception() {}
  virtual const char *what() const noexcept = 0;
};

class ExceptionMsg : public Exception
{
public:
  ExceptionMsg(const char *msg);
  virtual const char *what() const noexcept;

private:
  string msg_;
};

class ExceptionLine : public Exception
{
public:
  ExceptionLine(const char *filename,
		int line);

protected:
  const char *filename_;
  int line_;
};

// Failure opening filename for reading.
class FileNotReadable : public Exception
{
public:
  explicit FileNotReadable(const char *filename);
  virtual const char *what() const noexcept;

protected:
  const char *filename_;
};

// Failure opening filename for writing.
class FileNotWritable : public Exception
{
public:
  explicit FileNotWritable(const char *filename);
  virtual const char *what() const noexcept;

protected:
  const char *filename_;
};

// Report an error condition that should not be possible.
// The default handler prints msg to stderr and exits.
// The msg should NOT include a period or return.
// Only for use in those cases where a Report object is not available. 
#define criticalError(id,msg) \
  Report::defaultReport()->fileCritical(id, __FILE__, __LINE__, msg)

} // namespace
