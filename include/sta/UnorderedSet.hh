



#include <unordered_set>
#include <algorithm>

namespace sta {

// Add convenience functions around STL container.
template <class KEY, class HASH = std::hash<KEY>, class EQUAL = std::equal_to<KEY> >
class UnorderedSet : public std::unordered_set<KEY, HASH, EQUAL>
{
public:
  UnorderedSet() :
    std::unordered_set<KEY, HASH, EQUAL>()
  {
  }

  explicit UnorderedSet(size_t size) :
    std::unordered_set<KEY, HASH, EQUAL>(size)
  {
  }

  explicit UnorderedSet(size_t size,
			const HASH &hash,
			const EQUAL &equal) :
    std::unordered_set<KEY, HASH, EQUAL>(size, hash, equal)
  {
  }

  // Find out if key is in the set.
  bool
  hasKey(const KEY key) const
  {
    return this->find(key) != this->end();
  }

  // Find the value corresponding to key.
  KEY
  findKey(const KEY key) const
  {
    auto find_iter = this->find(key);
    if (find_iter != this->end())
      return *find_iter;
    else
      return nullptr;
  }

  void
  deleteContents()
  {
    Iterator iter(this);
    while (iter.hasNext())
      delete iter.next();
  }

  void
  deleteContentsClear()
  {
    deleteContents();
    std::unordered_set<KEY,HASH,EQUAL>::clear();
  }

  // Java style container itererator
  //  Set::Iterator<string *, Value, stringLess> iter(set);
  //  while (iter.hasNext()) {
  //    Value *v = iter.next();
  //  }
  class Iterator
  {
  public:
    Iterator() : container_(nullptr) {}
    explicit Iterator(std::unordered_set<KEY,HASH,EQUAL> *container) :
      container_(container)
    { if (container_ != nullptr) iter_ = container_->begin(); }
    explicit Iterator(std::unordered_set<KEY,HASH,EQUAL> &container) :
      container_(&container)
    { if (container_ != nullptr) iter_ = container_->begin(); }
    void init(std::unordered_set<KEY,HASH,EQUAL> *container)
    { container_ = container; if (container_ != nullptr) iter_=container_->begin();}
    void init(std::unordered_set<KEY,HASH,EQUAL> &container)
    { container_ = &container; if (container_ != nullptr) iter_=container_->begin();}
    bool hasNext() { return container_ != nullptr && iter_ != container_->end(); }
    KEY next() { return *iter_++; }
    std::unordered_set<KEY,HASH,EQUAL> *container() { return container_; }

  private:
    std::unordered_set<KEY,HASH,EQUAL> *container_;
    typename std::unordered_set<KEY,HASH,EQUAL>::iterator iter_;
  };

  class ConstIterator
  {
  public:
    ConstIterator() : container_(nullptr) {}
    explicit ConstIterator(const std::unordered_set<KEY,HASH,EQUAL> *container) :
      container_(container)
    { if (container_ != nullptr) iter_ = container_->begin(); }
    explicit ConstIterator(const std::unordered_set<KEY,HASH,EQUAL> &container) :
      container_(&container)
    { if (container_ != nullptr) iter_ = container_->begin(); }
    void init(const std::unordered_set<KEY,HASH,EQUAL> *container)
    { container_ = container; if (container_ != nullptr) iter_=container_->begin();}
    void init(const std::unordered_set<KEY,HASH,EQUAL> &container)
    { container_ = &container; if (container_ != nullptr) iter_=container_->begin();}
    bool hasNext() { return container_ != nullptr && iter_ != container_->end(); }
    KEY next() { return iter_++->second; }
    const std::unordered_set<KEY,HASH,EQUAL> *container() { return container_; }

  private:
    const std::unordered_set<KEY,HASH,EQUAL> *container_;
    typename std::unordered_set<KEY,HASH,EQUAL>::const_iterator iter_;
  };
};

} // namespace
