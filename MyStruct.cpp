
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

bool MDNSPH007::validTag(std::vector<std::string> &vec){
    //check if the opening tag and closing are on the same line

    std::size_t last = vec.size() - 1 ;

    std::size_t open = vec[0].find("<");
    std::size_t close = vec[last].find("</");

    if(open != std::string::npos && close != std::string::npos && vec.size()>1)
        return true;
    return false;
}
bool MDNSPH007::isValid(std::string &s){
  std::size_t open = s.find("<");
  std::size_t close = s.find("</");
  std::size_t flag = s.find("><");

  if(open != std::string::npos && close != std::string::npos && flag ==std::string::npos && close!=0){
      return true;
  }
  else{
      return false;
  }
}

std::vector<std::string> MDNSPH007::split(std::string s,std::string delimiter){
    std::size_t pos_start = 0, pos_end ,delimiter_len= delimiter.length();
    std::vector<std::string> v;
    std::string var;
    std::string open = "<";

    while((pos_end=s.find(delimiter,pos_start)) != std::string::npos){
        var = s.substr(pos_start,pos_end - pos_start);
        pos_start = pos_end + delimiter_len;
        v.push_back(var);
    }
    v.push_back(s.substr(pos_start));
    //Add the missing infomartion
    for(std::size_t i =0;i<v.size();++i){
        if(v[i].front() != '<')
            v[i].insert(0,"<");
        
        else if(v[i].back() != '>')
            v[i].append(">");
    }
    return v;
}

