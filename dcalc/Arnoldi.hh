

#include "parasitics/ConcreteParasiticsPvt.hh"

namespace sta
{

  struct delay_work;
  class GateTableModel;
  class Pin;

  // single-driver arnoldi model
  // A=U'*H*U, H is tri-diagonal matrix with d/e
  class arnoldi1
  {
  public:
    arnoldi1(){
      order = 0;
      n = 0;
      d = nullptr; // factor for normalization. w = w - d*u ?
      e = nullptr; // normalization, u = w/e
      U = nullptr; // base vector -> matrix
      ctot = 0.0; // total capacitance
      sqc = 0.0;  // sqrt（C)
    }
    ~arnoldi1();
    double elmore(int term_index);

    // calculate poles/residues for given rdrive
    void calculate_poles_res(delay_work *D, double rdrive);

  public:
    int order;  // How many iteration (columns) Ui
    int n;      // number of terms(nodes), including driver
    double *d;  // [order], diagonal
    double *e;  // [order-1], off-diagonal
    double **U; // [order][n], Ui vector
    double ctot;// total cap
    double sqc; // sqrt(c)
  };

  // This is the rcmodel, without Rd.
  // n is the number of terms
  // The vectors U[j] are of size n
  class rcmodel : public ConcreteParasitic, public arnoldi1
  {
  public:
    rcmodel();
    virtual ~rcmodel();
    virtual float capacitance() const;

    const Pin **pinV; // [n]
  };

  struct timing_table
  {
    const GateTableModel *table;
    const LibertyCell *cell;
    const Pvt *pvt;
    float in_slew;
    float relcap;
  };

  struct delay_c
  {
    double slew_derate;
    double vlo;
    double vhi;
    double vlg; // log(vhi/vlo)
    double smin; // minimum slew?
    double x1;
    double y1;
    double vmid; // falling convention, should be >= 0.5
  };

  // workspace for pole-residue -> delay calculations
  // delay_work
  // max order is 32
  struct delay_work
  {
    double slew_derate;
    double slew_factor; // (0,1.0] table_slew = slew_factor * full_slew
    delay_c cV[2];
    delay_c *c;

    double lo_thresh;
    double hi_thresh;

    int nmax;
    double poles[32]; // 1/tau
    double **resi;    // resi[jrec][h]  h=0,..order
    double *v[32];    // v
    double *w[32];    // w = RCU
    double aa[32];    // aa?
  };

} // namespace
