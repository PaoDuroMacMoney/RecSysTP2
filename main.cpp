/* 
 * File:   main.cpp
 * Author: rodrigo
 *
 * Created on 23 de Outubro de 2015, 17:45
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Util.h"
#include "Logger.h"

/*
 * 
 */
int main(int argc, char** argv) 
{
    std::system("clear");
    
    std::string content_path = argv[1];
    std::string ratings_path = argv[2];
    std::string targets_csv = argv[3];
    
    bool log = false;
    
    for(int i = 4; i< argc; i++)
    {        
        if(std::string(argv[i])=="-l")
        {   
            log = true;
        }
    }
    Logger::SetShouldLog(log);
    
    Logger::Log("Finished");
    
    Logger::Endl();
    Logger::Endl();
    return 0;
}

