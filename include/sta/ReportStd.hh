



namespace sta {

class Report;

// Make output streams that talk to stdout and stderr.
// This is useful for applications that do not link tcl.
Report *
makeReportStd();

} // namespace
