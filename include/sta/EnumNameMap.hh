



#include <map>
#include <string>

namespace sta {

using std::string;
using std::map;
using std::initializer_list;
using std::pair;

// Helper for mapping enum values to strings and back.
template <class ENUM>
class EnumNameMap
{
public:
  EnumNameMap(initializer_list<pair<const ENUM, string>> enum_names);
  const char *find(ENUM key) const;
  ENUM find(string name,
	    ENUM unknown_key) const;
  void find(string name,
	    // Return values.
	    ENUM &key,
	    bool &exists) const;
  
private:
  map<ENUM, string> enum_map_;
  map<string, ENUM> name_map_;
};

template <class ENUM>
EnumNameMap<ENUM>::EnumNameMap(initializer_list<pair<const ENUM, string>> enum_names) :
  enum_map_(enum_names)
{
  for (auto iter = enum_map_.begin(); iter != enum_map_.end(); iter++)
    name_map_[iter->second] = iter->first;
}

template <class ENUM>
const char *
EnumNameMap<ENUM>::find(ENUM key) const
{
  auto find_iter = enum_map_.find(key);
  if (find_iter != enum_map_.end())
    return find_iter->second.c_str();
  else
    return nullptr;
}

template <class ENUM>
void
EnumNameMap<ENUM>::find(string name,
			// Return values.
			ENUM &key,
			bool &exists) const
{
  auto find_iter = name_map_.find(name);
  if (find_iter != name_map_.end()) {
    key = find_iter->second;
    exists = true;
  }
  else
    exists = false;
}

template <class ENUM>
ENUM
EnumNameMap<ENUM>::find(string name,
			ENUM unknown_key) const
{
  auto find_iter = name_map_.find(name);
  if (find_iter != name_map_.end())
    return find_iter->second;
  else
    return unknown_key;
}

} // namespace
