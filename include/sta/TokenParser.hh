



namespace sta {

// Iterate over the tokens in str separated by character sep.
// Similar in functionality to strtok, but does not leave the string
// side-effected.  This is preferable to using strtok because it leaves
// string terminators where the separators were.
// Using STL string functions to parse tokens is messy and extremely slow
// on the RogueWave/Solaris implementation, apparently because of mutexes
// on temporary strings.
class TokenParser
{
public:
  TokenParser(const char *str,
	      const char *delimiters);
  bool hasNext();
  char *next();

private:
  const char *delimiters_;
  char *token_;
  char *token_end_;
  char token_delimiter_;
  bool first_;
};

} // namespace
