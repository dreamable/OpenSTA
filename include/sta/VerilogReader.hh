



namespace sta {

class NetworkReader;

// Return true if successful.
bool
readVerilogFile(const char *filename,
		NetworkReader *network);

void
deleteVerilogReader();

} // namespace sta

