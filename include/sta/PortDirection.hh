



#include "NetworkClass.hh"

namespace sta {

class PortDirection
{
public:
  static void init();
  static void destroy();
  // Singleton accessors.
  static PortDirection *input() { return input_; }
  static PortDirection *output() { return output_; }
  static PortDirection *tristate() { return tristate_; }
  static PortDirection *bidirect() { return bidirect_; }
  static PortDirection *internal() { return internal_; }
  static PortDirection *ground() { return ground_; }
  static PortDirection *power() { return power_; }
  static PortDirection *unknown() { return unknown_; }
  static PortDirection *find(const char *dir_name);
  const char *name() const { return name_; }
  int index() const { return index_; }
  bool isInput() const { return this == input_; }
  // Input or bidirect.
  bool isAnyInput() const;
  bool isOutput() const { return this == output_; }
  // Output, tristate or bidirect.
  bool isAnyOutput() const;
  bool isTristate() const { return this == tristate_; }
  bool isBidirect() const { return this == bidirect_; }
  // Bidirect or tristate.
  bool isAnyTristate() const;
  bool isGround() const { return this == ground_; }
  bool isPower() const { return this == power_; }
  // Ground or power.
  bool isPowerGround() const;
  bool isInternal() const { return this == internal_; }
  bool isUnknown() const { return this == unknown_; }

private:
  PortDirection(const char *name,
		int index);

  const char *name_;
  int index_;

  static PortDirection *input_;
  static PortDirection *output_;
  static PortDirection *tristate_;
  static PortDirection *bidirect_;
  static PortDirection *internal_;
  static PortDirection *ground_;
  static PortDirection *power_;
  static PortDirection *unknown_;
};

} // namespace
