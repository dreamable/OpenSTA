



#include <string>
#include <set>

namespace sta {

using std::string;
using std::set;

typedef set<string> StdStringSet;

class Path;
class StaState;

// Write a spice deck for path.
// Throws FileNotReadable, FileNotWritable, SubcktEndsMissing
void
writePathSpice(Path *path,
	       // Spice file written for path.
	       const char *spice_filename,
	       // Subckts used by path included in spice file.
	       const char *subckt_filename,
	       // File of all cell spice subckt definitions.
	       const char *lib_subckt_filename,
	       // Device model file included in spice file.
	       const char *model_filename,
	       // Nets off of path to include in the spice run.
               StdStringSet *off_path_pin_names,
               const char *power_name,
	       const char *gnd_name,
	       StaState *sta);

} // namespace
