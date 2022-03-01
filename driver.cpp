#include "Tag.h"

int main(int argc,char* argv[]){
    

    char user ;
    
    MDNSPH007::tag_v  v ; 
    
    //Prompt the user 
    std::cout<<"\'r\' (read and parse a specified input file)"<<'\n';
    std::cout<<"\'p\' (print all tags - this will list all the tags in arbitrary order, to cout)"<<'\n';
    std::cout<< "\'d\'(dump/write tags and data to a file called tag.txt see below)" <<'\n';
    std::cout<< "\'l\'(list/print tag data for given tag to cout)" <<'\n';
    std::cout<< "\'q\'(quit - terminate the input loop and exit the program)" <<'\n';
    std::cout << "Enter an option (r,p,d,l) or q to quit, and process return ..."<<std::endl;
    

    
    for(;;){
        
        std::cin>> user;
        if(user == 'q')
            break;
        switch(user){
            case 'r':
                if(argc == 1)
                    v = MDNSPH007::Data("sample.txt");
                else    
                    v = MDNSPH007::Data(argv[1]);
                break;
            
            case 'p':
                MDNSPH007::printAll(v);
                break;
            
            case 'd':
                MDNSPH007::writeData(v);
                break;
            
            case 'l':
                std::string s;
                std::cout<<"Enter the Tag name"<<std::endl;
                std::cin>> s;
                MDNSPH007::findTag(s,v);
                break;
    
        }

    }
   


    return 0;
}
