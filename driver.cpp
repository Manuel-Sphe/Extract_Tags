#include <sstream>
#include "Tag.h"
int main(void){
    std::vector<std::string> lns;
    MDNSPH007::readData("sample.txt",lns);
    //std::cout<<"The size is :"<<lns.size()<<std::endl;
    /*for(int i = 0;lns.size();i++){
        std::cout<<lns[i] <<std::endl;
    }*/

    std::string X  = "<h1>\nThe header\n</h1>"; 
    std::string value ;
    // for every line in the lns vector
    for(std::size_t i = 0 ;i< lns.size();i++){
        // read the line string input
        std::istringstream iss(lns[i]);
        // store the contents of the string to vector
        std::vector<std::string> myVec;

        int j = 0 ;
        while(!iss.eof()){
            iss >> value;
            myVec.push_back(value);
            //std::cout<<myVec[myVec.size()-1]<<std::endl;
    }

    std::cout<<myVec[myVec.size()-1] << std::endl;

    }
    
    
    return 0;
}
