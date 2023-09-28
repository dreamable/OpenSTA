



namespace sta {

class Network;
class LibertyLibrary;

LibertyLibrary *
readLibertyFile(const char *filename,
		bool infer_latches,
		Network *network);

} // namespace
