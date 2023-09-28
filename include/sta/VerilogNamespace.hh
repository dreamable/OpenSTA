



#include <string>

namespace sta {

using std::string;

string
instanceVerilogName(const char *sta_name,
		    const char escape);
string
netVerilogName(const char *sta_name,
	       const char escape);
string
portVerilogName(const char *sta_name,
		const char escape);

string
moduleVerilogToSta(const char *sta_name);
string
instanceVerilogToSta(const char *sta_name);
string
netVerilogToSta(const char *sta_name);
string
portVerilogToSta(const char *sta_name);

} // namespace
