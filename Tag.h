#ifndef MY_HDR
#define MY_HDR

#include <string>
#include <vector>
#include<iostream>
#include <sstream>



namespace MDNSPH007{

   
    struct TagStruct{
        std::string tag;
        std::string text;
        int pairs;
        TagStruct() : tag(""),text(""), pairs(0) {};
        TagStruct(std::string t ,std::string tx,int prs): tag(t),text(tx), pairs(prs){};// constructor
    };

    //std::vector<TagStruct> tags;

    // fuction declarations
    bool readData(std::string fileName, std::vector<std::string>  &vec);
    bool validTag(std::vector<std::string> &vec); // for checking the closing tags
    bool isValid(std::string &s);
    
    std::vector<std::string> split(std::string s,std::string delimiter);
    
    //std::string getTag(std::vector<std::string> &str);
}

#endif
