/* 
 * File:   Logger.h
 * Author: rodrigo
 *
 * Created on 31 de Outubro de 2015, 23:59
 */
#include <string>
#ifndef LOGGER_H
#define	LOGGER_H

class Logger
{
    public:        
        static void SetShouldLog(bool log);
        static void Log(std::string message);
        static void Endl();
    private:
        static Logger& getInstance()
        {
            static Logger instance; 
            return instance;
        }
        void setShouldLog(bool log);
        void log(std::string message);
        void endl();
        Logger() {};  
        bool should_log = false;

};

#endif	/* LOGGER_H */

