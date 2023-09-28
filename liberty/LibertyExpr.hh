



namespace sta {

class Report;
class FuncExpr;
class LibertyCell;

FuncExpr *
parseFuncExpr(const char *func,
	      LibertyCell *cell,
	      const char *error_msg,
	      Report *report);

} // namespace
