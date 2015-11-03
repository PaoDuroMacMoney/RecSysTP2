#include "Util.h"
#include "Logger.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream> 

content * read_content(std::string path)
{
    content * input = new content;

    input->length = 0;
    input->insert_index = 0;
    
    std::string line;
    std::ifstream myfile(path);

    Logger::Log("Counting lines");

    while (getline(myfile, line))
            input->length++;
    input->length--; //remove header from count
    int length = input->length;
    std::string text = std::to_string(length);
    text += " lines";
    Logger::Log(text);

    input->data = new content_node[input->length];

    std::ifstream infile(path);

    std::string header;
    getline(infile, header);//ignore header

    Logger::Log("Loading content to memory");
    infile >> *input;
    //while (infile >> *input){}

    Logger::Log("Content loaded...");

    return input;
}

std::istream & operator>>(std::istream & stream, content & input)
{
    //input format:
//    i0012278,{"Title":"The 'High Sign'","Year":"1921","Rated":"N/A","Released":"18 Apr 1921",
//            "Runtime":"21 min","Genre":"Short, Comedy","Director":"Edward F. Cline, Buster Keaton",
//            "Writer":"Edward F. Cline, Buster Keaton","Actors":"Buster Keaton",
//            "Plot":"Buster is thrown off a train near an amusement park. There he gets a job in a "
//    "shooting gallery run by the Blinking Buzzards mob. Ordered to kill a businessman, he winds up "
//    "protecting the man and his daughter by outfitting their home with trick devices.",
//            "Language":"English","Country":"USA","Awards":"N/A",
//            "Poster":"http://ia.media-imdb.com/images/M/MV5BMTc3ODY1MDg4Ml5BMl5BanBnXkFtZTcwMjYzMDE2MQ@@._V1_SX300.jpg",
//            "Metascore":"N/A","imdbRating":"7.7","imdbVotes":"1,502","imdbID":"tt0012278","Type":"movie","Response":"True"}
    std::string line;
    std::string garbage;
    std::string itemId, title, year, rated, released, runtime, genre, director,writer,actors, plot, language, country, awards;
    std::string poster, metascore, idmb_rating, idmb_votes, idmb_id, type, movie, response;
    if (std::getline(stream, line))
    {
        std::stringstream iss(line);

        if (std::getline(iss, itemId, ',') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, title, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, year, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, rated, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, released, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, runtime, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, genre, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, director, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, writer, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, actors, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, plot, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, language, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, country, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, awards, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, poster, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, metascore, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, idmb_rating, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, idmb_votes, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, idmb_id, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, type, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, movie, '"') && std::getline(iss, garbage, ':') && std::getline(iss, garbage, '"') &&
            std::getline(iss, response, '"') && std::getline(iss, garbage, '\n'))
        {
            content_node * node = new content_node;
            node->item_id = itemId;
            node->title = title;
            node->year = std::stoi(year);
            node->rated = rated;
            
            input.data[input.insert_index] = *node;
            input.insert_index++;
        }
        else
        {
            Logger::Log("Error dos brabos");
            stream.setstate(std::ios::failbit);
        }
    }
}