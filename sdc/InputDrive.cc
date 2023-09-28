

#include "InputDrive.hh"

namespace sta {

InputDrive::InputDrive()
{
  for (auto tr_index : RiseFall::rangeIndex()) {
    for (auto mm_index : MinMax::rangeIndex())
      drive_cells_[tr_index][mm_index] = nullptr;
  }
}

InputDrive::~InputDrive()
{
  for (auto tr_index : RiseFall::rangeIndex()) {
    for (auto mm_index : MinMax::rangeIndex()) {
      InputDriveCell *drive_cell = drive_cells_[tr_index][mm_index];
      delete drive_cell;
    }
  }
}

void
InputDrive::setSlew(const RiseFallBoth *rf,
		    const MinMaxAll *min_max,
		    float slew)
{
  slews_.setValue(rf, min_max, slew);
}

void
InputDrive::setDriveResistance(const RiseFallBoth *rf,
			       const MinMaxAll *min_max,
			       float res)
{
  drive_resistances_.setValue(rf, min_max, res);
}

void
InputDrive::driveResistance(const RiseFall *rf,
			    const MinMax *min_max,
			    float &res,
			    bool &exists)
{
  drive_resistances_.value(rf, min_max, res, exists);
}

bool
InputDrive::hasDriveResistance(const RiseFall *rf, const MinMax *min_max)
{
  return drive_resistances_.hasValue(rf, min_max);
}

bool
InputDrive::driveResistanceMinMaxEqual(const RiseFall *rf)
{
  float min_res, max_res;
  bool min_exists, max_exists;
  drive_resistances_.value(rf, MinMax::min(), min_res, min_exists);
  drive_resistances_.value(rf, MinMax::max(), max_res, max_exists);
  return min_exists && max_exists && min_res == max_res;
}

void
InputDrive::setDriveCell(const LibertyLibrary *library,
			 const LibertyCell *cell,
			 const LibertyPort *from_port,
			 float *from_slews,
			 const LibertyPort *to_port,
			 const RiseFallBoth *rf,
			 const MinMaxAll *min_max)
{
  for (auto rf_index : rf->rangeIndex()) {
    for (auto mm_index : min_max->rangeIndex()) {
      InputDriveCell *drive = drive_cells_[rf_index][mm_index];
      if (drive) {
	drive->setLibrary(library);
	drive->setCell(cell);
	drive->setFromPort(from_port);
	drive->setFromSlews(from_slews);
	drive->setToPort(to_port);
      }
      else {
	drive = new InputDriveCell(library, cell, from_port,
				   from_slews, to_port);
	drive_cells_[rf_index][mm_index] = drive;
      }
    }
  }
}

void
InputDrive::driveCell(const RiseFall *rf,
		      const MinMax *min_max,
                      // Return values.
		      const LibertyCell *&cell,
		      const LibertyPort *&from_port,
		      float *&from_slews,
		      const LibertyPort *&to_port)
{
  InputDriveCell *drive = drive_cells_[rf->index()][min_max->index()];
  if (drive) {
    cell = drive->cell();
    from_port = drive->fromPort();
    from_slews = drive->fromSlews();
    to_port = drive->toPort();
  }
  else {
    cell = nullptr;
    from_port = nullptr;
    from_slews = nullptr;
    to_port = nullptr;
  }
}

InputDriveCell *
InputDrive::driveCell(const RiseFall *rf,
		      const MinMax *min_max)
{
  return drive_cells_[rf->index()][min_max->index()];
}

bool
InputDrive::hasDriveCell(const RiseFall *rf,
			 const MinMax *min_max)
{
  return drive_cells_[rf->index()][min_max->index()] != nullptr;
}

bool
InputDrive::driveCellsEqual()
{
  int rise_index = RiseFall::riseIndex();
  int fall_index = RiseFall::fallIndex();
  int min_index = MinMax::minIndex();
  int max_index = MinMax::maxIndex();
  InputDriveCell *drive1 = drive_cells_[rise_index][min_index];
  InputDriveCell *drive2 = drive_cells_[rise_index][max_index];
  InputDriveCell *drive3 = drive_cells_[fall_index][min_index];
  InputDriveCell *drive4 = drive_cells_[fall_index][max_index];
  return drive1->equal(drive2)
    && drive1->equal(drive3)
    && drive1->equal(drive4);
}

void
InputDrive::slew(const RiseFall *rf,
		 const MinMax *min_max,
		 float &slew,
		 bool &exists)
{
  slews_.value(rf, min_max, slew, exists);
}

////////////////////////////////////////////////////////////////

InputDriveCell::InputDriveCell(const LibertyLibrary *library,
			       const LibertyCell *cell,
			       const LibertyPort *from_port,
			       float *from_slews,
			       const LibertyPort *to_port) :
  library_(library),
  cell_(cell),
  from_port_(from_port),
  to_port_(to_port)
{
  setFromSlews(from_slews);
}

void
InputDriveCell::setLibrary(const LibertyLibrary *library)
{
  library_ = library;
}

void
InputDriveCell::setCell(const LibertyCell *cell)
{
  cell_ = cell;
}

void
InputDriveCell::setFromPort(const LibertyPort *from_port)
{
  from_port_ = from_port;
}

void
InputDriveCell::setToPort(const LibertyPort *to_port)
{
  to_port_ = to_port;
}

void
InputDriveCell::setFromSlews(float *from_slews)
{
  for (auto tr_index : RiseFall::rangeIndex())
    from_slews_[tr_index] = from_slews[tr_index];
}

bool
InputDriveCell::equal(const InputDriveCell *drive) const
{
  int rise_index = RiseFall::riseIndex();
  int fall_index = RiseFall::fallIndex();
  return cell_ == drive->cell_
    && from_port_ == drive->from_port_
    && from_slews_[rise_index] == drive->from_slews_[rise_index]
    && from_slews_[fall_index] == drive->from_slews_[fall_index]
    && to_port_ == drive->to_port_;
}

} // namespace
