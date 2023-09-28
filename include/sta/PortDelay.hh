



#include "RiseFallMinMax.hh"
#include "SdcClass.hh"

namespace sta {

class PortDelay;

typedef Vector<PortDelay*> PortDelaySeq;

// set_input_delay arrival, set_output_delay departure
class PortDelay
{
public:
  RiseFallMinMax *delays() { return &delays_; }
  const Pin *pin() const { return pin_; }
  PinSet &leafPins() { return leaf_pins_; }
  Clock *clock() const;
  const ClockEdge *clkEdge() const { return clk_edge_; }
  bool sourceLatencyIncluded() const;
  void setSourceLatencyIncluded(bool included);
  bool networkLatencyIncluded() const;
  void setNetworkLatencyIncluded(bool included);
  const Pin *refPin() const { return ref_pin_; }
  void setRefPin(const Pin *ref_pin);
  RiseFall *refTransition() const;

protected:
  PortDelay(const Pin *pin,
	    const ClockEdge *clk_edge,
            const Network *network);

  const Pin *pin_;
  const ClockEdge *clk_edge_;
  bool source_latency_included_;
  bool network_latency_included_;
  const Pin *ref_pin_;
  RiseFallMinMax delays_;
  PinSet leaf_pins_;
};

class InputDelay : public PortDelay
{
public:
  int index() const { return index_; }

protected:
  InputDelay(const Pin *pin,
	     const ClockEdge *clk_edge,
	     int index,
	     const Network *network);

private:
  int index_;

  friend class Sdc;
};

class OutputDelay : public PortDelay
{
public:

protected:
  OutputDelay(const Pin *pin,
	      const ClockEdge *clk_edge,
	      const Network *network);

private:
  friend class Sdc;
};

// Prediate used to sort port delays.
class PortDelayLess
{
public:
  explicit PortDelayLess(const Network *network);
  bool operator()(const PortDelay *delay1,
		  const PortDelay *delay2) const;

private:
  const Network *network_;
};

} // namespace
