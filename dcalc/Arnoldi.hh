

// (c) 2018 Nefelus, Inc.
//
// Author: W. Scott



#include "parasitics/ConcreteParasiticsPvt.hh"

namespace sta {

struct delay_work;

class GateTableModel;
class Pin;

//
// single-driver arnoldi model
//
class arnoldi1
{
public:
  arnoldi1() { order=0; n=0; d=nullptr; e=nullptr; U=nullptr; ctot=0.0; sqc=0.0; }
  ~arnoldi1();
  double elmore(int term_index);

  //
  // calculate poles/residues for given rdrive
  //
  void calculate_poles_res(delay_work *D,double rdrive);

public:
  int order;
  int n;     // number of terms, including driver
  double *d; // [order]
  double *e; // [order-1]
  double **U; // [order][n]
  double ctot;
  double sqc;
};

// This is the rcmodel, without Rd.
// n is the number of terms
// The vectors U[j] are of size n
class rcmodel : public ConcreteParasitic,
		public arnoldi1
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

} // namespace
