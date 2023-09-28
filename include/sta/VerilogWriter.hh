



#include "NetworkClass.hh"

namespace sta {

void
writeVerilog(const char *filename,
	     bool sort,
	     bool include_pwr_gnd,
	     CellSeq *remove_cells,
	     Network *network);

} // namespace
