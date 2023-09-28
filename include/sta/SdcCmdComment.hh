



namespace sta {

class SdcCmdComment
{
public:
  SdcCmdComment();
  SdcCmdComment(const char *comment);
  const char *comment() { return comment_; }
  void setComment(const char *comment);

protected:
  // Destructor is protected to prevent deletion of a derived
  // class with a pointer to this base class.
  ~SdcCmdComment();

  char *comment_;
};

} // namespace
