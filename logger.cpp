#include <iostream>
#include <memory>
#include <string>
#include "logger.h"

std::shared_ptr<TLogger> TLogger::m_loggerInstance = nullptr;

TLogger::TLogger()
 : m_logLevel(ELogLevel::DEBUG)
{

}

void TLogger::log(std::string message, ELogLevel logLevel)
{
    std::string buff = "";

    if(logLevel <= m_logLevel)
    {
        switch(logLevel)
        {
            case ELogLevel::ERROR: buff += "\033[31m[ERROR] "; break;
            case ELogLevel::WARN: buff += "\033[33m[WARN] "; break;
            case ELogLevel::INFO: buff += "\033[32m[INFO] "; break;
            case ELogLevel::DEBUG: buff += "\033[0m[DEBUG] "; break;
            default: break;
        }

        buff += message + "\n";
        std::cout << buff;
    }
}

void TLogger::setLogLevel(ELogLevel logLevel)
{
    m_logLevel = logLevel;
}

std::shared_ptr<TLogger> TLogger::getInstance()
{
    if(m_loggerInstance == nullptr)
        m_loggerInstance = std::shared_ptr<TLogger>(new TLogger());

    return m_loggerInstance;
}