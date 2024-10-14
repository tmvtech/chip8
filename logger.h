#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <fstream>
#include <memory>

enum class ELogLevel
{
    NONE = 0,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4
};

class TLogger
{
    ELogLevel m_logLevel;
    static std::shared_ptr<TLogger> m_loggerInstance;

public:
    TLogger();
    void log(std::string message, ELogLevel logLevel);
    void setLogLevel(ELogLevel logLevel);

    static std::shared_ptr<TLogger> getInstance();
};

#endif