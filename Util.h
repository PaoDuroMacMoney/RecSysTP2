#pragma once

#include <string>
#include <vector>

struct content_node
{
    std::string item_id;
    std::string title;
    int year;
    std::string rated;
    std::string released;
    int runtime_minutes;
    std::string genre;
    std::string director;
    std::string writer;
    std::string actors;
    std::string plot;
    std::string language;
    std::string country;
    std::string awards;
    std::string poster;
    std::string metascore;
    float imdbRating;
    int imdbVotes;
    std::string imdbID;
    std::string type;
    bool response;    
};

class content
{
    friend std::istream & operator>>(std::istream & stream, content & input);
public:
    int length;
    int insert_index;
    content_node* data;
};

content * read_content(std::string path);
float tryConvertToFloat(std::string text);
int tryConvertToInt(std::string text);