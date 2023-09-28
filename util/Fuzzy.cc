

#include "Fuzzy.hh"

#include <algorithm> // max
#include <cmath> // abs

#include "MinMax.hh" // INF

namespace sta {

using std::max;
using std::abs;

constexpr static float float_equal_tolerance = 1E-15F;

bool
fuzzyEqual(float v1,
	   float v2)
{
  if (v1 == v2)
    return true;
  else if (v1 == 0.0)
    return abs(v2) < float_equal_tolerance;
  else if (v2 == 0.0)
    return abs(v1) < float_equal_tolerance;
  else
    return abs(v1 - v2) < 1E-6F * max(abs(v1), abs(v2));
}

bool
fuzzyZero(float v)
{
  return v == 0.0
    || abs(v) < float_equal_tolerance;
}

bool
fuzzyLess(float v1,
	  float v2)
{
  return v1 < v2 && !fuzzyEqual(v1, v2);
}

bool
fuzzyLessEqual(float v1,
	       float v2)
{
  return v1 < v2 || fuzzyEqual(v1, v2);
}

bool
fuzzyGreater(float v1,
	     float v2)
{
  return v1 > v2 && !fuzzyEqual(v1, v2);
}

bool
fuzzyGreaterEqual(float v1,
		  float v2)
{
  return v1 > v2 || fuzzyEqual(v1, v2);
}

bool
fuzzyInf(float value)
{
  return fuzzyEqual(value, INF)
    || fuzzyEqual(value, -INF);
}

} // namespace
