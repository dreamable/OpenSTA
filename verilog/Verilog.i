%module verilog

%{



#include "VerilogReader.hh"
#include "VerilogWriter.hh"
#include "Sta.hh"

using sta::Sta;
using sta::NetworkReader;
using sta::readVerilogFile;

%}

%inline %{

bool
read_verilog_cmd(const char *filename)
{
  Sta *sta = Sta::sta();
  NetworkReader *network = sta->networkReader();
  if (network) {
    sta->readNetlistBefore();
    return readVerilogFile(filename, network);
  }
  else
    return false;
}

void
delete_verilog_reader()
{
  deleteVerilogReader();
}

void
write_verilog_cmd(const char *filename,
		  bool sort,
		  bool include_pwr_gnd,
		  CellSeq *remove_cells)
{
  // This does NOT want the SDC (cmd) network because it wants
  // to see the sta internal names.
  Sta *sta = Sta::sta();
  Network *network = sta->network();
  writeVerilog(filename, sort, include_pwr_gnd, remove_cells, network);
  delete remove_cells;
}

%} // inline
