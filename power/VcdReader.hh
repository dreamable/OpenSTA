



#include "Vcd.hh"

namespace sta {

class StaState;

Vcd
readVcdFile(const char *filename,
            StaState *sta);

void
reportVcdWaveforms(const char *filename,
                   StaState *sta);

void
reportVcdVarValues(const char *filename,
                   const char *var_name,
                   StaState *sta);

} // namespace

