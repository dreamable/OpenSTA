



namespace sta {

class Report;
class LibertyCell;
class FuncExpr;

class LibExprParser
{
public:
  LibExprParser(const char *func,
		LibertyCell *cell,
		const char *error_msg,
		Report *report);
  ~LibExprParser();
  FuncExpr *makeFuncExprPort(const char *port_name);
  FuncExpr *makeFuncExprOr(FuncExpr *arg1,
			   FuncExpr *arg2);
  FuncExpr *makeFuncExprAnd(FuncExpr *arg1,
			    FuncExpr *arg2);
  FuncExpr *makeFuncExprXor(FuncExpr *arg1,
			    FuncExpr *arg2);
  FuncExpr *makeFuncExprNot(FuncExpr *arg);
  void setResult(FuncExpr *result);
  FuncExpr *result() { return result_; }
  void parseError(const char *msg);
  size_t copyInput(char *buf,
		   size_t max_size);
  void tokenStart();
  const char *token();
  char *tokenCopy();
  void tokenErase();
  void tokenAppend(char ch);

private:
  const char *func_;
  LibertyCell *cell_;
  const char *error_msg_;
  Report *report_;
  FuncExpr *result_;
  size_t token_length_;
  char *token_;
  char *token_next_;
};

extern LibExprParser *libexpr_parser;

} // namespace

// Global namespace

void
libertyExprFlushBuffer();
int
LibertyExprParse_error(const char *msg);
