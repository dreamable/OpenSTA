



namespace sta {

class StaState;
class Corner;

void
writeSdf(const char *filename,
	 Corner *corner,
	 char divider,
         bool include_typ,
	 int digits,
	 bool gzip,
	 bool no_timestamp,
	 bool no_version,
	 StaState *sta);

} // namespace
