
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
        //s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
        
        // replace tabs with spaces
        for(int i = 0 ;i<s.length();++i){
            if(s[i]=='\t')
                s[i] =' ';
        
        }
        
        // remove extra spaces from adjecent spaces 
        for(int i = 0 ;i<s.length()-1;++i){
            if(s[i]==s[i+1])
                s[i] ='\0';
        
        }
    }
    return s;
}

std::string MDNSPH007::getName(std::string s){
    std::size_t open = s.find("<"), close = s.find(">");// slash  = s.find("/");
    std::string hold = "";
    if(open !=n_pos && close != n_pos )
        hold = s.substr(open+1,close-1);
    return hold;
}

std::string MDNSPH007::find(str_vector vr, std::string s,int freq ){
    std::string line = "";
    for(std::size_t i = 0 ;i<vr.size(); i++){
        if( s == MDNSPH007::getName(vr[i]) && freq>1){
            
            line = line + " : " + MDNSPH007::getMessage(vr[i]); 

            line = line.substr(1,line.length()-1);
        }
        
        else if(s==MDNSPH007::getName(vr[i]) && freq==1)
            line = line+ MDNSPH007::getMessage(vr[i]);
        
       
    }
   
    return line;
}

MDNSPH007::tag_v MDNSPH007::Data(std::string filename="sample.txt"){

    std::vector<std::string> lns;
    std::vector<std::string> results;
    std::vector<MDNSPH007::TagStruct> tags;
    std::vector<int> couts;
    


    MDNSPH007::readData(filename,lns);
    std::string value ;
    std::stringstream i_ss;
    // for every line in the lns vector
    for(std::size_t i = 0 ;i< lns.size();i++){
        // read the line string input
        std::istringstream iss(lns[i]);

        std::vector<std::string> myVec;

        while(!iss.eof()){
            iss >> value;
            myVec.push_back(value);

        }

        if(MDNSPH007::validTag(myVec)){
            results.push_back(lns[i]);
        }

        else{
            if(MDNSPH007::isValid(lns[i])){
                results.push_back(lns[i]);
            }   
            else
                i_ss<<lns[i];
        }

    }
   
    for(std::size_t i =0;i<MDNSPH007::split(i_ss.str(),"><").size();++i){
        results.push_back(MDNSPH007::split(i_ss.str(),"><")[i]);
    }

    // stores the tags and their frequencies 
    std::unordered_map<std::string,int> hash;
    for(std::size_t i = 0 ;i<results.size();++i){
        std::string text = MDNSPH007::getName(results[i]);
        if(text!="")
            hash[text]++;
    }
    
    std::unordered_map<std::string, int>:: iterator p;

    for (p = hash.begin(); p != hash.end(); p++){
       
        tags.push_back(MDNSPH007::TagStruct(p->first,MDNSPH007::find(results,p->first,p->second),p->second));
    }

    // clear the string stream 
    i_ss.clear();
    i_ss.str("");

    return tags;
}

void MDNSPH007::printAll(MDNSPH007::tag_v tags){
    //std::cout<<tags.size()<<'\n';
    for(auto i :tags)
        std::cout<<"\""<<i.tag<< "\"" <<", "<<i.pairs<<", "<<"\""<< i.text<<"\""<<std::endl;
}

void MDNSPH007::writeData(MDNSPH007::tag_v tags){

    std::ofstream outfile("tags.txt");
    for(auto i :tags){
        outfile<<"\""<< i.tag<<"\""<<", "<<i.pairs<<", "<<"\""<<i.text <<"\"" <<std::endl;
    }
    outfile.close();

}

void MDNSPH007::findTag(std::string a,MDNSPH007::tag_v data){
    for(auto i :data){
        if(i.tag == a)
            std::cout<<"\""<<i.tag<< "\"" <<", "<<i.pairs<<", "<<"\""<< i.text<<"\""<<std::endl;
        else{
            std::cout<< "No Tag information to displays"<<std::endl;
            break;
        }    
            
    }     
}

