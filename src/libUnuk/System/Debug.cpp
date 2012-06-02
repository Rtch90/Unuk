#include <iostream>
#include <fstream>
#include <cstdarg>
#include <ctime>
#include "Debug.h"
#include "string"


using namespace std;

// ===================================================================
// The Debug log allows us to display ever piece of data that
// populates our class components, anything that is loaded, serialized,
// de-serialized etc will be printed out to a text file.
// (Running our program in a terminal, this debug log will print to it.)
// ===================================================================

Debug *Debug::logger = NULL;

Debug::Debug(bool logToFile) {
  time_t timestamp;
  if(logToFile) {
    _logFile.open("../Bin/Debug.log", ios::out);
    if(!logToFile) {
      // We can not open our log.
      cerr << "Warning: Can not open Debug.log to write, continueing without logging\n";
    } else {
      // Log File is open, let us give it a nice time stamp.
      timestamp = time(NULL);
      _logFile << "Log Started: " << ctime(&timestamp) << endl;
    }
  }
}

Debug::~Debug(void) {
  time_t timestamp;

  // We only need to close the log if it is open.
  if(_logFile) {
    // Give it a closing timestamp.
    timestamp = time(NULL);
    _logFile << endl << "Log Closed: " << ctime(&timestamp) << endl;

    // Close the log file.
    _logFile.close();
  }
}

void Debug::message(std::string msg) {
  if(_logFile) {
    _logFile << msg << endl;
  }
  cerr << msg << endl << endl;
}

void Debug::message(const char *msg, ...) {
  va_list vargList; // This is to handlle the variable arguments

  char outBuf[1024];
  unsigned short outLen;

  // This takes the arguments and puts them into the character array.
  va_start(vargList, msg);

#if defined WIN32
  outLen = (unsigned short)_vsnprintf(outBuf, sizeof(outBuf), msg, vargList);
#else
  outLen = vsnprintf(outBuf, sizeof(outBuf), msg, vargList);
#endif

  va_end(vargList);

  if(outLen >= sizeof(outBuf)) {
    outLen = sizeof(outBuf);
  }

  if(_logFile) {
    _logFile << outBuf << endl;
  }

  cerr << outBuf << endl;
}

bool Debug::openLog(bool logToFile) {
  // Make sure the logger has not already been initialized.
  if(logger != NULL) {
    logger->message("Warning: Multiple calls to openLog().");
    return false;
  }
  logger = new Debug(logToFile);
  return true;
}

void Debug::closeLog(void) {
  if(logger == NULL) {
    cerr << "Warning: Call to closeLog() with NULL logger pointer." << endl;
    return;
  }
  delete logger;
  logger = NULL;
}
