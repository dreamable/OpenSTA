

#include "FuncExpr.hh"

#include <algorithm> // min
#include "Report.hh"
#include "StringUtil.hh"
#include "Liberty.hh"
#include "LibertyExprPvt.hh"

extern int
LibertyExprParse_parse();

namespace sta {

LibExprParser *libexpr_parser;

FuncExpr *
parseFuncExpr(const char *func,
	      LibertyCell *cell,
	      const char *error_msg,
	      Report *report)
{
  if (func != nullptr && func[0] != '\0') {
    LibExprParser parser(func, cell, error_msg, report);
    libexpr_parser = &parser;
    LibertyExprParse_parse();
    FuncExpr *expr = parser.result();
    libexpr_parser = nullptr;
    return expr;
  }
  else
    return nullptr;
}

LibExprParser::LibExprParser(const char *func,
			     LibertyCell *cell,
			     const char *error_msg,
			     Report *report) :
  func_(func),
  cell_(cell),
  error_msg_(error_msg),
  report_(report),
  result_(nullptr),
  token_length_(100),
  token_(new char[token_length_]),
  token_next_(token_)
{
}

LibExprParser::~LibExprParser()
{
  stringDelete(token_);
}

LibertyPort *
libertyReaderFindPort(LibertyCell *cell,
                      const char *port_name);

FuncExpr *
LibExprParser::makeFuncExprPort(const char *port_name)
{
  FuncExpr *expr = nullptr;
  LibertyPort *port = libertyReaderFindPort(cell_, port_name);
  if (port)
    expr = FuncExpr::makePort(port);
  else
    report_->warn(7, "%s references unknown port %s.",
                  error_msg_, port_name);
  stringDelete(port_name);
  return expr;
}

FuncExpr *
LibExprParser::makeFuncExprNot(FuncExpr *arg)
{
  if (arg)
    return FuncExpr::makeNot(arg);
  else
    return nullptr;
}

FuncExpr *
LibExprParser::makeFuncExprXor(FuncExpr *arg1,
			       FuncExpr *arg2)
{
  if (arg1 && arg2)
    return FuncExpr::makeXor(arg1, arg2);
  else
    return nullptr;
}

FuncExpr *
LibExprParser::makeFuncExprAnd(FuncExpr *arg1,
			       FuncExpr *arg2)
{
  if (arg1 && arg2)
    return FuncExpr::makeAnd(arg1, arg2);
  else
    return nullptr;
}

FuncExpr *
LibExprParser::makeFuncExprOr(FuncExpr *arg1,
			      FuncExpr *arg2)
{
  if (arg1 && arg2)
    return FuncExpr::makeOr(arg1, arg2);
  else
    return nullptr;
}

void
LibExprParser::setResult(FuncExpr *result)
{
  result_ = result;
}

size_t
LibExprParser::copyInput(char *buf,
			 size_t max_size)
{
  strncpy(buf, func_, max_size);
  int count = strlen(buf);
  func_ += count;
  return count;
}

char *
LibExprParser::tokenCopy()
{
  return stringCopy(token_);
}

void
LibExprParser::tokenErase()
{
  token_next_ = token_;
}

void
LibExprParser::tokenAppend(char ch)
{
  if (token_next_ + 1 - token_ >= static_cast<signed int>(token_length_)) {
    size_t index = token_next_ - token_;
    token_length_ *= 2;
    char *prev_token = token_;
    token_ = new char[token_length_];
    strcpy(token_, prev_token);
    stringDelete(prev_token);
    token_next_ = &token_[index];
  }
  *token_next_++ = ch;
  // Make sure the token is always terminated.
  *token_next_ = '\0';
}

void
LibExprParser::parseError(const char *msg)
{
  report_->error(206, "%s %s.", error_msg_, msg);
}

} // namespace

////////////////////////////////////////////////////////////////
// Global namespace

int
LibertyExprParse_error(const char *msg)
{
  libertyExprFlushBuffer();
  sta::libexpr_parser->parseError(msg);
  return 0;
}
