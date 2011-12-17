#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <fstream>
#include "string"

class Debug {
public:
  Debug(bool logToFile);
  ~Debug(void);

  // Log an error message.
  void message(std::string msg);
  void message(const char *msg, ...);
  static bool openLog(bool logToFile);
  static void closeLog(void);
  
  static Debug *logger;

private: 
  std::ofstream _logFile;
};

#endif // _DEBUG_H_
