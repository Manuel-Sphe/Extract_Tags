
#include "Tag.h"
#include <fstream>
bool MDNSPH007::readData(std::string fileName,std::vector<std::string> &vec){

    std::ifstream fileIn(fileName.c_str());

    while(!fileIn){
        std::cerr<<"File Not Found !!!"<<std::endl;
        return false;
    }
    
    // else- go here

    std::string line;

    while(std::getline(fileIn,line)){
        vec.push_back(line);
    }

    fileIn.close();
    
    return true;

}
