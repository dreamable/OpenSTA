



#include "Set.hh"
#include "NetworkClass.hh"

namespace sta {

class HpinDrvrLoad;
class HpinDrvrLoadVisitor;

void
visitHpinDrvrLoads(const Pin *pin,
		   const Network *network,
		   HpinDrvrLoadVisitor *visitor);

class HpinDrvrLoadLess
{ 
public:
  bool operator()(const HpinDrvrLoad *drvr_load1,
		  const HpinDrvrLoad *drvr_load2) const;
};

// Abstract base class for visitDrvrLoadsThruHierPin visitor.
class HpinDrvrLoadVisitor
{
public:
  HpinDrvrLoadVisitor() {}
  virtual ~HpinDrvrLoadVisitor() {}
  virtual void visit(HpinDrvrLoad *drvr_load) = 0;
};

class HpinDrvrLoad
{
public:
  HpinDrvrLoad(const Pin *drvr,
	       const Pin *load,
	       PinSet *hpins_from_drvr,
	       PinSet *hpins_to_load);
  ~HpinDrvrLoad();
  void report(const Network *network);
  HpinDrvrLoad(const Pin *drvr,
	       const Pin *load);
  const Pin *drvr() const { return drvr_; }
  const Pin *load() const { return load_; }
  PinSet *hpinsFromDrvr() { return hpins_from_drvr_; }
  PinSet *hpinsToLoad() { return hpins_to_load_; }
  void setDrvr(const Pin *drvr);
 
private:
  const Pin *drvr_;
  const Pin *load_;
  PinSet *hpins_from_drvr_;
  PinSet *hpins_to_load_;
};

} // namespace
