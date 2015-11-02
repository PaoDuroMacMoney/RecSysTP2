/* 
 * File:   Logger.cpp
 * Author: rodrigo
 * 
 * Created on 31 de Outubro de 2015, 23:59
 */
#include <iostream>
#include "Logger.h"

void Logger::SetShouldLog(bool log)
{
    Logger::getInstance().setShouldLog(log);
}

void Logger::Log(std::string message)
{
    Logger::getInstance().log(message);
}

void Logger::Endl()
{
    Logger::getInstance().endl();
}

void Logger::setShouldLog(bool log)
{
    should_log = log;
}

void Logger::log(std::string message)
{
    if(should_log)
    {
        std::cout<<message;
    }
}

void Logger::endl()
{
    if(should_log)
    {
        std::cout<<std::endl;
    }
}
