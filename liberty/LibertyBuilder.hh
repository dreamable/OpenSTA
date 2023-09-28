



#include "Vector.hh"
#include "Transition.hh"
#include "LibertyClass.hh"
#include "ConcreteLibrary.hh"

namespace sta {

class TimingArcAttrs;
class InternalPowerAttrs;
class LeakagePowerAttrs;
class Debug;
class Report;

class LibertyBuilder
{
public:
  LibertyBuilder() {}
  virtual ~LibertyBuilder() {}
  void init(Debug *debug,
            Report *report);
  virtual LibertyCell *makeCell(LibertyLibrary *library,
				const char *name,
				const char *filename);
  virtual LibertyPort *makePort(LibertyCell *cell,
				const char *name);
  virtual LibertyPort *makeBusPort(LibertyCell *cell,
				   const char *bus_name,
				   int from_index,
				   int to_index,
                                   BusDcl *bus_dcl);
  virtual LibertyPort *makeBundlePort(LibertyCell *cell,
				      const char *name,
				      ConcretePortSeq *members);
  // Build timing arc sets and their arcs given a type and sense.
  // Port functions and cell latches are also used by this builder
  // to get the correct roles.
  TimingArcSet *makeTimingArcs(LibertyCell *cell,
			       LibertyPort *from_port,
			       LibertyPort *to_port,
			       LibertyPort *related_out,
			       TimingArcAttrsPtr attrs,
                               int line);
  InternalPower *makeInternalPower(LibertyCell *cell,
				   LibertyPort *port,
				   LibertyPort *related_port,
				   InternalPowerAttrs *attrs);
  LeakagePower *makeLeakagePower(LibertyCell *cell,
				 LeakagePowerAttrs *attrs);

  TimingArcSet *makeFromTransitionArcs(LibertyCell *cell,
				       LibertyPort *from_port,
				       LibertyPort *to_port,
				       LibertyPort *related_out,
				       RiseFall *from_rf,
				       TimingRole *role,
				       TimingArcAttrsPtr attrs);
  TimingArcSet *makeCombinationalArcs(LibertyCell *cell,
				      LibertyPort *from_port,
				      LibertyPort *to_port,
				      LibertyPort *related_out,
				      bool to_rise,
				      bool to_fall,
				      TimingArcAttrsPtr attrs);

protected:
  ConcretePort *makeBusPort(const char *name,
			    int from_index,
			    int to_index,
			    ConcretePortSeq *members);
  void makeBusPortBits(ConcreteLibrary *library,
		       LibertyCell *cell,
		       ConcretePort *bus_port,
		       const char *bus_name,
		       int from_index,
		       int to_index);
  // Bus port bit (internal to makeBusPortBits).
  virtual LibertyPort *makePort(LibertyCell *cell,
                                const char *bit_name,
                                int bit_index);
  void makeBusPortBit(ConcreteLibrary *library,
		      LibertyCell *cell,
		      ConcretePort *bus_port,
		      const char *bus_name,
		      int index);
  virtual TimingArcSet *makeTimingArcSet(LibertyCell *cell,
					 LibertyPort *from,
					 LibertyPort *to,
					 LibertyPort *related_out,
					 TimingRole *role,
					 TimingArcAttrsPtr attrs);
  virtual TimingArc *makeTimingArc(TimingArcSet *set,
				   Transition *from_rf,
				   Transition *to_rf,
				   TimingModel *model);
  TimingArc *makeTimingArc(TimingArcSet *set,
			   RiseFall *from_rf,
			   RiseFall *to_rf,
			   TimingModel *model);
  TimingArcSet *makeLatchDtoQArcs(LibertyCell *cell,
				  LibertyPort *from_port,
				  LibertyPort *to_port,
                                  TimingSense sense,
				  LibertyPort *related_out,
				  TimingArcAttrsPtr attrs);
  TimingArcSet *makeRegLatchArcs(LibertyCell *cell,
				 LibertyPort *from_port,
				 LibertyPort *to_port,
				 LibertyPort *related_out,
				 RiseFall *from_rf,
				 TimingArcAttrsPtr attrs);
  TimingArcSet *makePresetClrArcs(LibertyCell *cell,
				  LibertyPort *from_port,
				  LibertyPort *to_port,
				  LibertyPort *related_out,
				  RiseFall *to_rf,
				  TimingArcAttrsPtr attrs);
  TimingArcSet *makeTristateEnableArcs(LibertyCell *cell,
				       LibertyPort *from_port,
				       LibertyPort *to_port,
				       LibertyPort *related_out,
				       bool to_rise,
				       bool to_fall,
				       TimingArcAttrsPtr attrs);
  TimingArcSet *makeTristateDisableArcs(LibertyCell *cell,
					LibertyPort *from_port,
					LibertyPort *to_port,
					LibertyPort *related_out,
					bool to_rise,
					bool to_fall,
					TimingArcAttrsPtr attrs);

  Debug *debug_;
  Report *report_;
};

} // namespace
