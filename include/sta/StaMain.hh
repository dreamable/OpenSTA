



struct Tcl_Interp;

namespace sta {

class Sta;

// Parse command line argument
int
staTclAppInit(int argc,
	      char *argv[],
	      const char *init_filename,
	      Tcl_Interp *interp);

// Sta initialization.
// Makes the Sta object and registers TCL commands.
void
initSta(int argc,
	char *argv[],
	Tcl_Interp *interp);

// TCL init files are encoded into the string init using the three
// digit decimal equivalent for each ascii character.  This function
// unencodes the string and evals it.  This packages the TCL init
// files as part of the executable so they don't have to be shipped as
// separate files that have to be located and loaded at run time.
void
evalTclInit(Tcl_Interp *interp,
	    const char *inits[]);
char *
unencode(const char *inits[]);

bool
findCmdLineFlag(int &argc,
		char *argv[],
		const char *flag);
char *
findCmdLineKey(int &argc,
	       char *argv[],
	       const char *key);

int
parseThreadsArg(int &argc,
		char *argv[]);
int
sourceTclFile(const char *filename,
	      bool echo,
	      bool verbose,
	      Tcl_Interp *interp);
bool
is_regular_file(const char *filename);

} // namespace
