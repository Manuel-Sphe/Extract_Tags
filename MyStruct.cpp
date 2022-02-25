
#include "Tag.h"
#include <fstream>
bool MDNSPH007::readData(std::string fileName,str_vector &vec){

    std::ifstream fileIn(fileName.c_str());

    while(!fileIn){
        std::cerr<<"File Not Found !!!"<<std::endl;
        return false;
    }

    std::string line;

    while(std::getline(fileIn,line)){

      // line.erase( std::remove( line.begin(), line.end(), '\t'), line.end());

       //std::replace (line.begin(), line.end(),'\t', ' ');

        vec.push_back(line);
    }

    fileIn.close();

    return true;

}

bool MDNSPH007::validTag(str_vector &vec){
    //check if the opening tag and closing are on the same line

    std::size_t last = vec.size() - 1 ;

    std::size_t open = vec[0].find("<");
    std::size_t close = vec[last].find("</");

    // {<tag>man, is, happy</tag>}

    if(open !=n_pos && close !=n_pos && vec.size()>1 )
        return true;
    else if(vec.size() == 1 && MDNSPH007::isValid(vec[0]))
        return true;
    else
        return false;
}

bool MDNSPH007::isValid(std::string &s){
    std::size_t open = s.find("<"),close = s.find("</"),flag = s.find("><");
    std::size_t l_open = s.rfind("<"), l_close = s.find(">"); // the last < and >
  
    if(open != n_pos && close != n_pos && flag ==n_pos && close!=0 && open!=l_open && close != l_close){
        return true;
    }
    else{
        return false;
    }
}

str_vector MDNSPH007::split(std::string s,std::string delimiter){
    std::size_t pos_start = 0, pos_end ,delimiter_len= delimiter.length();
    str_vector v;
    std::string var;
    std::string open = "<";

    
    if (s.find("><") == n_pos){
        v.push_back("");
        return v;
    }
       
    while((pos_end=s.find(delimiter,pos_start)) != n_pos){
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

std::string MDNSPH007::getMessage(std::string s){
    std::size_t f = s.find(">"),l = s.rfind("<"), len = s.length(), l_index = len -1 ;

    if(f !=n_pos && l != n_pos){
        f++; l--; // exluding < and >

        s = s.substr(f,len - f - (l_index - l) );
    }

    // need to remove extra spaces and tabs
       

    return s;
}
