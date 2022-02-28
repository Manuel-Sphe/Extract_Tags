#ifndef MY_HDR
#define MY_HDR

#include <string>
#include <vector>
#include<iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#define n_pos std::string::npos
#define str_vector std::vector<std::string>



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
    bool readData(std::string fileName, str_vector  &vec);
    bool validTag(str_vector &vec); // for checking the closing tags
    bool isValid(std::string &s);
    
    str_vector split(std::string s,std::string delimiter);
    std::string getMessage(std::string s);
    std::string getName(std::string s);

    int getCount(str_vector &res,std::string s);

    std::string find(str_vector vr,std::string s, int freq);

    typedef std::vector<MDNSPH007::TagStruct> tag_v;
    
   tag_v Data(std::string filename);
   
   void printAll(tag_v vec);
   void writeData(tag_v tags);
   void findTag(std::string s,  tag_v vc );
    
    //std::string getTag(std::vector<std::string> &str);
}



#endif
