#ifndef __CMDLINEPARSER_H__
#define __CMDLINEPARSER_H__

#include <iostream>

#include "logger.h"

class TCmdLineParser {

    // Logging
    std::shared_ptr<TLogger> m_logger;

    std::string m_romFileName;
    int m_logLevel;

    void printHelpMessage();
    void setRomFileName(std::string new_name);
    void setLogLevel(int logLevel);
public:
    TCmdLineParser();
    void parseCmdLine(int argc, char** argv);

    bool isRomFileNameSet();
    std::string getRomFileName();
    bool isLogLevelSet();
    int getLogLevel();
};

#endif
