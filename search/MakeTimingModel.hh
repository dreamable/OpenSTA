



namespace sta {

class LibertyLibrary;
class Corner;
class Sta;

LibertyLibrary *
makeTimingModel(const char *lib_name,
                const char *cell_name,
                const char *filename,
                const Corner *corner,
                Sta *sta);

} // namespace
