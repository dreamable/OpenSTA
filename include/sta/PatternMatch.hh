



#include <string>

#include "Error.hh"

// Don't require all of tcl.h.
typedef struct Tcl_RegExp_ *Tcl_RegExp;
typedef struct Tcl_Interp Tcl_Interp;

namespace sta {

using ::Tcl_RegExp;
using ::Tcl_Interp;

class PatternMatch
{
public:
  // If regexp is false, use unix glob style matching.
  // If regexp is true, use TCL regular expression matching.
  //   Regular expressions are always anchored.
  // If nocase is true, ignore case in the pattern.
  // Tcl_Interp is optional for reporting regexp compile errors.
  PatternMatch(const char *pattern,
	       bool is_regexp,
	       bool nocase,
	       Tcl_Interp *interp);
  // Use unix glob style matching.
  PatternMatch(const char *pattern);
  PatternMatch(const char *pattern,
	       const PatternMatch *inherit_from);
  PatternMatch(const string &pattern,
	       const PatternMatch *inherit_from);
  bool match(const char *str) const;
  bool match(const string &str) const;
  bool matchNoCase(const char *str) const;
  const char *pattern() const { return pattern_; }
  bool isRegexp() const { return is_regexp_; }
  bool nocase() const { return nocase_; }
  Tcl_Interp *tclInterp() const { return interp_; }
  bool hasWildcards() const;

private:
  void compileRegexp();

  const char *pattern_;
  bool is_regexp_;
  bool nocase_;
  Tcl_Interp *interp_;
  Tcl_RegExp regexp_;
};

// Error thrown by Pattern constructor.
class RegexpCompileError : public Exception
{
public:
  explicit RegexpCompileError(const char *pattern);
  virtual ~RegexpCompileError() noexcept {}
  virtual const char *what() const noexcept;

private:
  std::string error_;
};

// Simple pattern match
// '*' matches zero or more characters
// '?' matches any character
bool
patternMatch(const char *pattern,
	     const char *str);
bool
patternMatchNoCase(const char *pattern,
		   const char *str,
		   bool nocase);
// Predicate to find out if there are wildcard characters in the pattern.
bool
patternWildcards(const char *pattern);

} // namespace
