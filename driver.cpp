#include "Tag.h"
int main(void){
    std::vector<std::string> lns;
    std::vector<std::string> results;
    std::vector<MDNSPH007::TagStruct> tags;


    MDNSPH007::readData("sample.txt",lns);
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
            //std::cout<< lns[i]<<"\n";
        }

        else{
            if(MDNSPH007::isValid(lns[i])){
                results.push_back(lns[i]);
            }   
            else
                i_ss<<lns[i];
        }

    }
      //std::cout <<i_ss.str();
    for(std::size_t i =0;i<MDNSPH007::split(i_ss.str(),"><").size();++i){
        //oresults.push_back(MDNSPH007::split(i_ss.str(),"><")[i]);
    }
    

    for(std::size_t i =0;i<results.size();++i){
        std::cout<< results[i]<<"\n";
        //std::cout<<MDNSPH007::getMessage(results[i])<<"\n";
    }

    i_ss.clear();
    i_ss.str("");

      /*for(std::size_t j = 0;j<results.size();j++){
            std::cout << results[j]<< '\n';
      }*/

    return 0;
}
