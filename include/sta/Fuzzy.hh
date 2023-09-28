



namespace sta {

// "Fuzzy" floating point comparisons that allow some tolerance.

bool
fuzzyEqual(float v1,
	   float v2);
bool
fuzzyZero(float v);
bool
fuzzyLess(float v1,
	  float v2);
bool
fuzzyLessEqual(float v1,
	       float v2);
bool
fuzzyGreater(float v1,
	     float v2);
bool
fuzzyGreaterEqual(float v1,
		  float v2);
bool
fuzzyInf(float value);

} // namespace
