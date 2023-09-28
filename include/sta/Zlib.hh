



// The zlib package is optional.
// Define stdio based macros if it is missing.

#include "StaConfig.hh"  // ZLIB

#ifdef ZLIB_FOUND

#include <zlib.h>

#else // ZLIB_FOUND

#include <cstdio>

#define gzFile FILE*
#define gzopen fopen
#define gzclose fclose
#define gzgets(stream,s,size) fgets(s,size,stream)
#define gzprintf fprintf
#define Z_NULL nullptr

#endif // ZLIB_FOUND
