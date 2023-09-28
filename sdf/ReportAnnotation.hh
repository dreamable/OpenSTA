



namespace sta {

class StaState;

void
reportAnnotatedDelay(bool report_cells,
		     bool report_nets,
		     bool report_in_ports,
		     bool report_out_ports,
		     int max_lines,
		     bool list_annotated,
		     bool list_unannotated,
		     bool report_constant_arcs,
		     StaState *sta);
void
reportAnnotatedCheck(bool report_setup,
		     bool report_hold,
		     bool report_recovery,
		     bool report_removal,
		     bool report_nochange,
		     bool report_width,
		     bool report_period,
		     bool report_max_skew,
		     int max_lines,
		     bool list_annotated,
		     bool list_unannotated,
		     bool report_constant_arcs,
		     StaState *sta);

} // namespace
