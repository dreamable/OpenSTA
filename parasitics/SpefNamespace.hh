



namespace sta {

// Translate from spf/spef namespace to sta namespace.
// Caller owns the result string.
char *
spefToSta(const char *token, char spef_divider,
	  char path_escape, char path_divider);
// Translate from sta namespace to spf/spef namespace.
// Caller owns the result string.
char *
staToSpef(const char *token, char spef_divider,
	  char path_divider, char path_escape);


} // namespace
