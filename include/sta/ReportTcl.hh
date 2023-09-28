



#include <tcl.h>

#include "Report.hh"

namespace sta {

// Encapsulate the Tcl stdout and stderr channels to print to the
// report object so that the output from Tcl puts and errors can be
// logged and redirected.
//
// Output streams that talk to TCL channels.
// This directs all output on the Report object to the Tcl stdout channel.
// Tcl output channels are encapsulated to print to the Report object
// that supports redirection and logging as well as printing to the
// underlying channel.
class ReportTcl : public Report
{
public:
  ReportTcl();
  virtual ~ReportTcl();
  virtual void logBegin(const char *filename);
  virtual void logEnd();
  virtual void redirectFileBegin(const char *filename);
  virtual void redirectFileAppendBegin(const char *filename);
  virtual void redirectFileEnd();
  virtual void redirectStringBegin();
  virtual const char *redirectStringEnd();
  // This must be called after the Tcl interpreter has been constructed.
  // It makes the encapsulated channels.
  virtual void setTclInterp(Tcl_Interp *interp);

protected:
  virtual size_t printConsole(const char *buffer,
                              size_t length);
  void flush();

private:
  Tcl_ChannelType *makeEncapChannelType(Tcl_Channel channel,
					char *channel_name,
					Tcl_DriverOutputProc output_proc);
  size_t printTcl(Tcl_Channel channel,
                  const char *buffer,
                  size_t length);

  Tcl_Interp *interp_;
  // The original tcl channels.
  Tcl_Channel tcl_stdout_;
  Tcl_Channel tcl_stderr_;
  // Encapsulated channels that print on this object.
  Tcl_Channel tcl_encap_stdout_;
  Tcl_Channel tcl_encap_stderr_;
};

} // namespace
