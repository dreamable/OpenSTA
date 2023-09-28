



namespace sta {

// Java style container iterator.
//  Iterator<Object*> iter(container);
//  while (iter.hasNext()) {
//    Object *obj = iter.next();
//  }
template <class OBJ>
class Iterator
{
public:
  virtual ~Iterator() {}
  virtual bool hasNext() = 0;
  virtual OBJ next() = 0;
};

} // namespace
