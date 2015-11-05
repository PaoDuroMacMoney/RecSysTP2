#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
struct training_instance
{
    std::string * features;
    float * feature_values;
    int length;
};

struct training_data
{
    training_instance * instances;
    float * values;
    int length;
};

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

class dictionary
{
public:
    void update(std::string word);
private:
    std::map<std::string, int> * data = new std::map<std::string, int>;
    int length;
};

class content
{
    friend std::istream & operator>>(std::istream & stream, content & input);    
public:
    void updateTitleDictionary(content_node * node);
    void updateDescriptionDictionary(content_node * node);
    int length;
    int insert_index;
    content_node* data;
    dictionary * title_dictionary = new dictionary;
    dictionary * description_dictionary = new dictionary;
private:
    void updateDictionary(dictionary * dictionary_to_update, std::string text);
};

content * read_content(std::string path);
float tryConvertToFloat(std::string text);
int tryConvertToInt(std::string text);
std::map<std::string, int> * buildDictionary(content * content_input);

std::unordered_set<std::string> * getStopWords();