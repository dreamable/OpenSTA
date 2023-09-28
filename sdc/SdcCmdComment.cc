

#include "StringUtil.hh"
#include "SdcCmdComment.hh"

namespace sta {

SdcCmdComment::SdcCmdComment() :
  comment_(nullptr)
{
}

SdcCmdComment::SdcCmdComment(const char *comment)
{
  comment_ = nullptr;
  if (comment && comment[0] != '\0')
    comment_ = stringCopy(comment);
}
  
SdcCmdComment::~SdcCmdComment()
{
  stringDelete(comment_);
}
void
SdcCmdComment::setComment(const char *comment)
{
  if (comment_)
    stringDelete(comment_);
  comment_ = nullptr;
  if (comment && comment[0] != '\0')
    comment_ = stringCopy(comment);
}

} // namespace
