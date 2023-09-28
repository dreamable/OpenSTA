

#include "TokenParser.hh"

#include <cctype>
#include <cstring>

namespace sta {

TokenParser::TokenParser(const char *str,
                         const char *delimiters) :
  delimiters_(delimiters),
  token_(const_cast<char*>(str)),
  token_delimiter_('\0'),
  first_(true)
{
  // Skip leading spaces.
  while (*token_ != '\0' && isspace(*token_))
    token_++;
  token_end_ = strpbrk(token_, delimiters_);
  if (token_end_) {
    // Save the delimiter.
    token_delimiter_ = *token_end_;
    // Replace the separator with a terminator.
    *token_end_ = '\0';
  }
}

bool
TokenParser::hasNext()
{
  if (!first_) {
    // Replace the previous separator.
    if (token_end_) {
      *token_end_ = token_delimiter_;
      token_ = token_end_ + 1;
      // Skip spaces.
      while (*token_ != '\0' && isspace(*token_))
	token_++;
      // Skip delimiters.
      while (*token_ != '\0' && strchr(delimiters_,*token_) != nullptr)
        token_++;
      if (*token_ == '\0')
	token_ = nullptr;
      else {
	token_end_ = strpbrk(token_, delimiters_);
	if (token_end_) {
	  // Save the delimiter.
	  token_delimiter_ = *token_end_;
	  // Replace the separator with a terminator.
	  *token_end_ = '\0';
	}
      }
    }
    else
      token_ = nullptr;
  }
  return token_ != nullptr;
}

char *
TokenParser::next()
{
  first_ = false;
  return token_;
}

} // namespace
