



namespace sta {

class ArcDelayCalc;
class StaState;

ArcDelayCalc *
makeDmpCeffElmoreDelayCalc(StaState *sta);
ArcDelayCalc *
makeDmpCeffTwoPoleDelayCalc(StaState *sta);

// Delay calculator using Dartu/Menezes/Pileggi effective capacitance
// algorithm for RSPF loads.
class DmpCeffDelayCalc : public RCDelayCalc
{
public:
  DmpCeffDelayCalc(StaState *sta);
  virtual ~DmpCeffDelayCalc();
  virtual void inputPortDelay(const Pin *port_pin,
			      float in_slew,
			      const RiseFall *rf,
			      const Parasitic *parasitic,
			      const DcalcAnalysisPt *dcalc_ap);
  virtual void gateDelay(const LibertyCell *drvr_cell,
			 const TimingArc *arc,
			 const Slew &in_slew,
			 float load_cap,
			 const Parasitic *drvr_parasitic,
			 float related_out_cap,
			 const Pvt *pvt,
			 const DcalcAnalysisPt *dcalc_ap,
			 // return values
			 ArcDelay &gate_delay,
			 Slew &drvr_slew);
  virtual float ceff(const LibertyCell *drvr_cell,
		     const TimingArc *arc,
		     const Slew &in_slew,
		     float load_cap,
		     const Parasitic *drvr_parasitic,
		     float related_out_cap,
		     const Pvt *pvt,
		     const DcalcAnalysisPt *dcalc_ap);
  virtual string reportGateDelay(const LibertyCell *drvr_cell,
                                 const TimingArc *arc,
                                 const Slew &in_slew,
                                 float load_cap,
                                 const Parasitic *drvr_parasitic,
                                 float related_out_cap,
                                 const Pvt *pvt,
                                 const DcalcAnalysisPt *dcalc_ap,
                                 int digits);
  virtual void copyState(const StaState *sta);

protected:
  void gateDelaySlew(double &delay,
		     double &slew);
  void loadDelaySlew(const Pin *load_pin,
		     double elmore,
		     ArcDelay &delay,
		     Slew &slew);
  // Select the appropriate special case Dartu/Menezes/Pileggi algorithm.
  void setCeffAlgorithm(const LibertyLibrary *library,
			const LibertyCell *cell,
			const Pvt *pvt,
			const GateTableModel *gate_model,
			const RiseFall *rf,
			double in_slew,
			float related_out_cap,
			double c2,
			double rpi,
			double c1);

  static bool unsuppored_model_warned_;

private:
  // Dmp algorithms for each special pi model case.
  // These objects are reused to minimize make/deletes.
  DmpCap *dmp_cap_;
  DmpPi *dmp_pi_;
  DmpZeroC2 *dmp_zero_c2_;
  DmpAlg *dmp_alg_;
};

// PiElmore parasitic delay calculator using Dartu/Menezes/Pileggi
// effective capacitance and elmore delay.
class DmpCeffElmoreDelayCalc : public DmpCeffDelayCalc
{
public:
  DmpCeffElmoreDelayCalc(StaState *sta);
  ArcDelayCalc *copy() override;
  void gateDelay(const LibertyCell *drvr_cell,
                 const TimingArc *arc,
                 const Slew &in_slew,
                 float load_cap,
                 const Parasitic *drvr_parasitic,
                 float related_out_cap,
                 const Pvt *pvt,
                 const DcalcAnalysisPt *dcalc_ap,
                 // Return values.
                 ArcDelay &gate_,
                 Slew &drvr_slew) override;
  void loadDelay(const Pin *load_pin,
                 ArcDelay &wire_delay,
                 Slew &load_slew) override;
};

// PiPoleResidue parasitic delay calculator using Dartu/Menezes/Pileggi
// effective capacitance and two poles/residues.
class DmpCeffTwoPoleDelayCalc : public DmpCeffDelayCalc
{
public:
  DmpCeffTwoPoleDelayCalc(StaState *sta);
  ArcDelayCalc *copy() override;
  Parasitic *findParasitic(const Pin *drvr_pin,
                           const RiseFall *rf,
                           const DcalcAnalysisPt *dcalc_ap) override;
  ReducedParasiticType reducedParasiticType() const override;
  void inputPortDelay(const Pin *port_pin,
                      float in_slew,
                      const RiseFall *rf,
                      const Parasitic *parasitic,
                      const DcalcAnalysisPt *dcalc_ap) override;
  void gateDelay(const LibertyCell *drvr_cell,
                 const TimingArc *arc,
                 const Slew &in_slew,
                 float load_cap,
                 const Parasitic *drvr_parasitic,
                 float related_out_cap,
                 const Pvt *pvt,
                 const DcalcAnalysisPt *dcalc_ap,
                 // Return values.
                 ArcDelay &gate_delay,
                 Slew &drvr_slew) override;
  void loadDelay(const Pin *load_pin,
                 ArcDelay &wire_delay,
                 Slew &load_slew) override;

private:
  void loadDelay(Parasitic *pole_residue,
		 double p1,
		 double k1,
		 ArcDelay &wire_delay,
		 Slew &load_slew);
  float loadDelay(double vth,
		  double p1,
		  double p2,
		  double k1,
		  double k2,
		  double B,
		  double k1_p1_2,
		  double k2_p2_2,
		  double tt,
		  double y_tt);

  bool parasitic_is_pole_residue_;
  float vth_;
  float vl_;
  float vh_;
  float slew_derate_;
};


} // namespace
