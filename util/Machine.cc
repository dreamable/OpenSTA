

#if defined(_WIN32)
  #include "MachineWin32.cc"
#elif defined(__APPLE__)
  #include "MachineApple.cc"
#elif defined(__linux__)
  #include "MachineLinux.cc"
#else
  #include "MachineUnknown.cc"
#endif
