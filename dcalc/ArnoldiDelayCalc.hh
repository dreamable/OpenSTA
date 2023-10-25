



namespace sta {

class ArcDelayCalc;
class StaState;

ArcDelayCalc *
makeArnoldiDelayCalc(StaState *sta);

class ArnoldiDelayCalc : public RCDelayCalc {
 public:
  ArnoldiDelayCalc();
  virtual ~ArnoldiDelayCalc();
  virtual ArcDelayCalc* copy();
  virtual Parasitic* findParasitic(const NlPin* drvr_pin,
                                   PinCapMap* pin_caps,
                                   Parasitics* parasitics,
                                   Transition rf,
                                   const DcalcAnalysisPt* dcalc_ap);
  virtual ReducedParasiticType reducedParasiticType() const;
  virtual bool gateDelay(const LibCell* drvr_cell,
                         LibTimingArc* arc,
                         Transition in_tran,
                         Transition out_tran,
                         const TimingValue& in_slew,
                         float load_cap,
                         Parasitic* drvr_parasitic,
                         float related_out_cap,
                         const Pvt* pvt,
                         const DcalcAnalysisPt* dcalc_ap,
                         // Return values.
                         TimingValue& gate_delay,
                         TimingValue& drvr_slew);
  virtual void loadDelay(const NlPin* load_pin,
                         LibPin* lib_pin,
                         ArcDelay& wire_delay,
                         TimingValue& load_slew);
  virtual void inputPortDelay(const NlPin* port_pin,
                              LibPin* lib_pin,
                              float in_slew,
                              Transition rf,
                              Parasitic* parasitic,
                              const DcalcAnalysisPt* dcalc_ap);
  virtual void reportGateDelay(const LibCell* drvr_cell,
                               LibTimingArc* arc,
                               const Slew& in_slew,
                               float load_cap,
                               Parasitic*,
                               float related_out_cap,
                               const Pvt* pvt,
                               const DcalcAnalysisPt* dcalc_ap,
                               int digits,
                               string* result);

 private:
  bool gateDelaySlew(const LibCell* drvr_cell,
                     LibTimingArc* timing_arc,
                     Transition in_tran,
                     Transition out_tran,
                     const TimingValue& in_slew,
                     float related_out_cap,
                     const Pvt* pvt,
                     // Return values.
                     TimingValue& gate_delay,
                     TimingValue& drvr_slew);
  void delay_work_set_thresholds(delay_work* D,
                                 double lo,
                                 double hi,
                                 bool rising,
                                 double derate);
  bool ar1_ceff_delay(delay_work* D, timing_table* tab, arnoldi1* mod, double* delays, double* slews);
  double ra_rdelay_1(timing_table* tab,
                     double ctot);
  double ra_get_r(delay_work* D,
                  timing_table* tab,
                  double rdelay,
                  double ctot);
  double ra_get_s(delay_work* D,
                  timing_table* tab,
                  double r,
                  double c);
  void ra_solve_for_s(delay_work* D,
                      double p,
                      double tlohi,
                      double& s);
  // from poles and residues, solve for t20,t50,t80
  // solve for one value v
  void pr_solve1(double s,
                 int order,
                 double* p,
                 double* rr,
                 double v1,
                 double* t1);
  // solve for three values: vhi,vmid,vlo
  void pr_solve3(double s,
                 int order,
                 double* p,
                 double* rr,
                 double vhi,
                 double* thi,
                 double vmid,
                 double* tmid,
                 double vlo,
                 double* tlo);

  //
  // routines for linear drive model and ceff
  //
  double pr_ceff(double s,
                 double rdrive,
                 int order,
                 double* p,
                 double* rr,
                 double ceff_time);
  double ra_solve_for_t(double p,
                        double s,
                        double v);
  void ra_solve_for_pt(double ps,
                       double v,
                       double* pt,
                       double* d);
  void ra_calc_c(double lo,
                 double hi,
                 double* c_smin,
                 double* c_x1,
                 double* c_y1);

  rcmodel* rcmodel_;
  int _pinNmax;
  double* _delayV;
  double* _slewV;
  int pin_n_;
  bool input_port_;
  ArnoldiReduce* reduce_;
  delay_work* delay_work_;
};


} // namespace
