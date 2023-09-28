

%exception {
  try { $function }
  catch (std::bad_alloc &) {
    fprintf(stderr, "Error: out of memory.\n");
    exit(1);
  }
  catch (std::exception &excp) {
    Tcl_ResetResult(interp);
    Tcl_AppendResult(interp, "Error: ", excp.what(), nullptr);
    return TCL_ERROR;
  }
}
