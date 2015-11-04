/* 
 * File:   main.cpp
 * Author: rodrigo
 *
 * Created on 23 de Outubro de 2015, 17:45
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "Util.h"
#include "Logger.h"

/*
 * 
 */
int main(int argc, char** argv) 
{
    int call = std::system("clear");
    
    argv[1] = "content.csv";
    argv[2] = "ratings.csv";
    argv[3] = "targets.csv";
    argv[4] = "-l";
    argc = 5;
    
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
    
    Logger::Log(content_path);
    
    content * input_content = read_content(content_path);
    
    Logger::Log("Finished");
    Logger::Endl();
    return 0;
}

