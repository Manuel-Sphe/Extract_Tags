#ifndef MY_HDR
#define MY_HDR

#include <string>
#include <vector>
#include<iostream>

namespace MDNSPH007{
    struct TagStruct{
        std::string tag;
        std::string text;
        int pairs;
        TagStruct() : tag(""),text(""), pairs(0) {};
        TagStruct(std::string t ,std::string tx,int prs): tag(t),text(tx), pairs(prs){};// constructor
    };

    //std::vector<TagStruct> tags;
    bool readData(std::string fileName, std::vector<std::string> &vec);
   
}

#endif
