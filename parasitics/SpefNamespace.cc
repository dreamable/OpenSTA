

#include "SpefNamespace.hh"

#include <cctype>
#include <cstring>

namespace sta {

char *
spefToSta(const char *token,
          char spef_divider,
	  char path_divider,
          char path_escape)
{
  const char spef_escape = '\\';
  char *trans_token = new char[strlen(token) + 1];
  char *t = trans_token;

  for (const char *s = token; *s ; s++) {
    char ch = *s;
    if (ch == spef_escape) {
      char next_ch = s[1];
      if (next_ch == spef_divider) {
	// Translate spef escape to network escape.
	*t++ = path_escape;
	// Translate spef divider to network divider.
	*t++ = path_divider;
      }
      else if (next_ch == '['
	       || next_ch == ']'
	       || next_ch == spef_escape) {
	// Translate spef escape to network escape.
	*t++ = path_escape;
	*t++ = next_ch;
      }
      else
	// No need to escape other characters.
	*t++ = next_ch;
      s++;
    }
    else if (ch == spef_divider)
      // Translate spef divider to network divider.
      *t++ = path_divider;
    else
      // Just the normal noises.
      *t++ = ch;
  }
  *t++ = '\0';
  return trans_token;
}

char *
staToSpef(const char *token,
          char spef_divider,
	  char path_divider,
          char path_escape)
{
  const char spef_escape = '\\';
  char *trans_token = new char[strlen(token) + 1];
  char *t = trans_token;

  for (const char *s = token; *s ; s++) {
    char ch = *s;
    if (ch == path_escape) {
      char next_ch = s[1];
      if (next_ch == path_divider) {
	// Translate network escape to spef escape.
	*t++ = spef_escape;
	// Translate network divider to spef divider.
	*t++ = spef_divider;
      }
      else if (next_ch == '['
	       || next_ch == ']') {
	// Translate network escape to spef escape.
	*t++ = spef_escape;
	*t++ = next_ch;
      }
      else
	// No need to escape other characters.
	*t++ = next_ch;
      s++;
    }
    else if (ch == path_divider)
      // Translate network divider to spef divider.
      *t++ = spef_divider;
    else if (!(isdigit(ch) || isalpha(ch) || ch == '_')) {
      // Escape non-alphanum characters.
      *t++ = spef_escape;
      *t++ = ch;
    }
    else
      // Just the normal noises.
      *t++ = ch;
  }
  *t++ = '\0';
  return trans_token;
}

} // namespace
