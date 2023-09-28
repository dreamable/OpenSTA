



#include <string>

namespace sta {

using std::string;

// Return true if name is a bus.
bool
isBusName(const char *name,
	  const char brkt_left,
	  const char brkt_right,
	  char escape);

// Parse name as a bus.
// signal
//  bus_name = nullptr
// bus[bit]
//  bus_name = "bus"
//  index = bit
// Caller must delete returned bus_name string.
void
parseBusName(const char *name,
	     const char brkt_left,
	     const char brkt_right,
	     char escape,
	     // Return values.
	     bool &is_bus,
             string &bus_name,
	     int &index);
// Allow multiple different left/right bus brackets.
void
parseBusName(const char *name,
	     const char *brkts_left,
	     const char *brkts_right,
	     char escape,
	     // Return values.
	     bool &is_bus,
	     string &bus_name,
	     int &index);

// Parse a bus range, such as BUS[4:0].
// bus_name is set to null if name is not a range.
// Caller must delete returned bus_name string.
void
parseBusName(const char *name,
             const char brkt_left,
             const char brkt_right,
             char escape,
             // Return values.
             bool &is_bus,
             bool &is_range,
             string &bus_name,
             int &from,
             int &to,
             bool &subscript_wild);

// brkt_lefts and brkt_rights are corresponding strings of legal
// bus brackets such as "[(<" and "])>".
void
parseBusName(const char *name,
             const char *brkts_left,
             const char *brkts_right,
             const char escape,
             // Return values.
             bool &is_bus,
             bool &is_range,
             string &bus_name,
             int &from,
             int &to,
             bool &subscript_wild);

// Insert escapes before ch1 and ch2 in token.
string
escapeChars(const char *token,
	    const char ch1,
	    const char ch2,
	    const char escape);

} // namespace
